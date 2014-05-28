#pragma once

#include "stdafx.h"
#include <string>
#include <ctime>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <numeric>
#include <algorithm>
#include "GeneticAlgorithm.h"

float GeneticAlgorithm::CalculateLocalFitnessFunction(char**** population, int individual, int teacher, float didacticDissatisfactionWeight, 
													  float organizationalDissatisfactionWeight)
{
	float result = CheckLessonsDistribution(teacher,individual,population)*didacticDissatisfactionWeight;
	result += CheckLessonsCirculation(teacher,individual,population)*organizationalDissatisfactionWeight;

	return result;
}

float * GeneticAlgorithm::CalculateObjectiveFunction(char**** population, int p_size, float infeasibilitiesWeight, float didacticDissatisfactionWeight, 
													 float organizationalDissatisfactionWeight)
{
	float * result = new float[p_size];
	std::fill(result, result + p_size, 0.);
	int infeasibilitiesCount = 0;
	for (int i = 0; i < p_size; i++)
	{
		result[i] = CheckFeasibility(i, population) * infeasibilitiesWeight + CheckDidacticRequirements(i, population) * didacticDissatisfactionWeight 
			+ CheckOrganizationalRequirements(i, population) * organizationalDissatisfactionWeight;
	}
	return result;
}

int GeneticAlgorithm::CheckFeasibility(int individual, char ****population)
{
	int infeasibilitiesCount = 0;

	int ** curriculum = new int*[classes_count];
	for (int i = 0; i < classes_count; i++)
	{
		curriculum[i] = new int[teachers_count];
		std::fill(curriculum[i],curriculum[i]+teachers_count,0);
	}

	bool * isClassBusy = new bool[classes_count];

	for (int h = 0; h < hours_per_day; h++)
	{
		for (int d = 0; d < days; d++)
		{
			std::fill(isClassBusy,isClassBusy+classes_count,false);
			for (int t = 0; t < teachers_count; t++)
			{
				int actualClass = FindIndexOfClass(population[individual][t][d][h]);
				if (actualClass == -1 && population[individual][t][d][h] != fixed_hour_symbol 
					&& population[individual][t][d][h] != free_hour_symbol) throw std::domain_error("Class does not exist");
				if(actualClass >= 0)
				{
					if(isClassBusy[actualClass])
						infeasibilitiesCount++;
					isClassBusy[actualClass] = true;
					curriculum[actualClass][t]++;
				}
			}
		}
	}

	/*for (int c = 0; c < classes_count; c++)
	{
		for (int t = 0; t < teachers_count; t++)
		{
			infeasibilitiesCount += std::abs(classes_curriculum[c][t] - curriculum[c][t]); 
		}
	}*/

	int * lastClassLesson = new int[classes_count];

	/*for (int d = 0; d < days; d++)
	{
		std::fill(lastClassLesson,lastClassLesson+classes_count,-1);
		for (int h = 0; h < hours_per_day; h++)
		{
			for (int t = 0; t < teachers_count; t++)
			{
				int actualClass = FindIndexOfClass(population[individual][t][d][h]);
				if (actualClass == -1 && population[individual][t][d][h] != fixed_hour_symbol 
					&& population[individual][t][d][h] != free_hour_symbol) throw std::domain_error("Class does not exist");
				if(actualClass >= 0)
				{
					if(lastClassLesson[actualClass] != -1 && lastClassLesson[actualClass] != h - 1)
						infeasibilitiesCount += h - lastClassLesson[actualClass];
					lastClassLesson[actualClass] = h;
				}
			}
		}
	}*/

	delete[] lastClassLesson;
	delete[] isClassBusy;
	for (int i = 0; i < classes_count; i++)
	{
		delete[] curriculum[i];
	}
	delete[] curriculum;
	return infeasibilitiesCount;
}

float GeneticAlgorithm::CheckDidacticRequirements(int individual, char ****population)
{
	float didacticDissatisfaction = 0;

	for (int t = 0; t < teachers_count; t++)
		didacticDissatisfaction += CheckLessonsDistribution(t, individual, population);

	return didacticDissatisfaction;
}

float GeneticAlgorithm::CheckLessonsDistribution(int teacher, int individual, char ****population)
{
	float result = 0.0f;
	float avgLessonsCount = CalculateTeacherLessonsCount(teacher) / (float)days;
	float max_hours_for_teacher_per_day = std::min(avgLessonsCount + 2, (float)hours_per_day - 2);
	int lastLessonCount = 0;
	int * lastClassLesson = new int[classes_count];
	for (int d = 0; d < days; d++)
	{
		int lessons = 0;
		std::fill(lastClassLesson,lastClassLesson+classes_count,-1);
		for (int h = 0; h < hours_per_day; h++)
		{
			int actualClass = -1;
			if((actualClass = FindIndexOfClass(population[individual][teacher][d][h])) >=0 )
			{
				if(lastClassLesson[actualClass] != -1 && lastClassLesson[actualClass] != h - 1)
					result += h - lastClassLesson[actualClass];
				lastClassLesson[actualClass] = h;
				lessons++;
				if(h == hours_per_day - 1)
					lastLessonCount++;
			}
		}
		if(lessons > max_hours_for_teacher_per_day)
			result += lessons - max_hours_for_teacher_per_day;
		result += std::abs(lessons - avgLessonsCount);
	}
	if(lastLessonCount > max_last_lessons_count)
		result += lastLessonCount - max_last_lessons_count;

	delete[] lastClassLesson;

	return result;
}

float GeneticAlgorithm::CheckOrganizationalRequirements(int individual, char ****population)
{
	float organizationalDissatisfaction = 0;

	for (int t = 0; t < teachers_count; t++)
		organizationalDissatisfaction += CheckLessonsCirculation(t,individual,population);

	return organizationalDissatisfaction;
}

float GeneticAlgorithm::CheckLessonsCirculation(int teacher, int individual, char **** population)
{
	float result = 0.0f;
	for (int d = 0; d < days; d++)
	{
		float avgLessonsCount = CalculateTeacherLessonsCount(teacher) / (float)days;
		float min_hours_for_teacher_per_day = std::max(avgLessonsCount - 2, (float)2);
		int lessons = 0;
		for (int h = 0; h < hours_per_day; h++)
		{
			if(FindIndexOfClass(population[individual][teacher][d][h]) >=0 )
				lessons++;
		}
		if(lessons < min_hours_for_teacher_per_day)
			result += min_hours_for_teacher_per_day - lessons;

		int lastTeacherLesson = -1;
		for (int h = 0; h < hours_per_day; h++)
		{
			int actualClass = FindIndexOfClass(population[individual][teacher][d][h]);
			if (actualClass == -1 && population[individual][teacher][d][h] != fixed_hour_symbol 
				&& population[individual][teacher][d][h] != free_hour_symbol) throw std::domain_error("Class does not exist");
			if(actualClass >= 0)
			{
				if(lastTeacherLesson != -1 && lastTeacherLesson != h - 1)
					result += h - lastTeacherLesson;
				lastTeacherLesson = h;
			}
		}
	}

	return result;
}

int GeneticAlgorithm::FindIndexOfClass(char c)
{
	for (int i = 0; i < classes_count; i++)
	{
		if(classes[i] == c)
			return i;
	}
	return -1;
}

int GeneticAlgorithm::CalculateTeacherLessonsCount(int teacher)
{
	int result = 0;
	for (int c = 0; c < classes_count; c++)
	{
		result += classes_curriculum[c][teacher];
	}
	return result;
}