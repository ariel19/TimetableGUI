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

int GeneticAlgorithm::days = 5;
int GeneticAlgorithm::hours_per_day = 6;
int GeneticAlgorithm::max_last_lessons_count = 2;
int GeneticAlgorithm::max_iterations = 100;
char GeneticAlgorithm::fixed_hour_symbol = '#';
char GeneticAlgorithm::free_hour_symbol = '-';

GeneticAlgorithm::GeneticAlgorithm(std::vector<std::string> _teachers, std::vector<char> _classes,
								   std::vector<int> _hours_for_classes, std::vector<std::vector<int>> _classes_curriculum,
								   std::vector<std::vector<std::pair<int, int>>> _fixed_hours, int _population_size)
{

	teachers_count = _teachers.size();
	classes_count = _classes.size();

	teachers = _teachers;
	classes = _classes;
	population_size = _population_size;
	fixed_hours = _fixed_hours;
	hours_for_classes = _hours_for_classes;
	classes_curriculum = _classes_curriculum;

	// Tworzenie planow
	timetables = new char***[population_size];

	for(int individual = 0; individual < population_size; ++individual)
	{
		timetables[individual] = new char**[teachers_count];

		for(int teacher = 0; teacher < teachers_count; ++teacher)
		{
			timetables[individual][teacher] = new char*[days];

			for(int day = 0; day < days; ++day)
			{
				timetables[individual][teacher][day] = new char[hours_per_day];
				memset(timetables[individual][teacher][day], 0, hours_per_day);
			}
		}
	}
	
	std::ofstream myfile;
	myfile.open ("manual_file.txt");

	myfile << "Teachers" << std::endl;
	for (int i = 0; i < teachers.size(); ++i)
		myfile << teachers[i] << std::endl;
	myfile << "==========" << std::endl;

	myfile << "Classes" << std::endl;
	for (int i = 0; i < classes.size(); ++i)
		myfile << classes[i] << std::endl;
	myfile << "==========" << std::endl;

	myfile << "Hours for classes" << std::endl;
	for (int i = 0; i < hours_for_classes.size(); ++i)
		myfile << hours_for_classes[i] << std::endl;
	myfile << "==========" << std::endl;

	myfile << "Classes curriculum" << std::endl;
	for (int i = 0; i < classes_curriculum.size(); ++i) {
		myfile << i << ":\n";
		for (int j = 0; j < classes_curriculum[i].size(); ++j)
			myfile << classes_curriculum[i][j] << std::endl;
	}
	myfile << "==========" << std::endl;

	myfile << "Fixed hours" << std::endl;
	for (int i = 0; i < fixed_hours.size(); ++i) {
		myfile << i << ":\n";
		for (int j = 0; j < fixed_hours[i].size(); ++j)
			myfile << fixed_hours[i][j].first << " " << fixed_hours[i][j].second << std::endl;
	}
	myfile << "==========" << std::endl;

	myfile.close();
}

GeneticAlgorithm::~GeneticAlgorithm()
{
	for(int individual = 0; individual < population_size; ++individual)
	{
		for(int teacher = 0; teacher < teachers_count; ++teacher)
		{
			for(int day = 0; day < days; ++day)
			{
				delete [] timetables[individual][teacher][day];
			}

			delete [] timetables[individual][teacher];
		}

		delete [] timetables[individual];
	}

	delete [] timetables;
}

void GeneticAlgorithm::PrintTimetable(char ***timetable, std::ostream &out)
{
	out << std::endl;

	for(int teacher = 0; teacher < teachers_count; ++teacher)
	{
		out << std::setw(30) << std::left << teachers[teacher];

		for(int day = 0; day < days; ++day)
		{
			for(int hour = 0; hour < hours_per_day; ++hour)
			{
				out << timetable[teacher][day][hour];
			}

			out << "   ";
		}

		out << std::endl;
	}

	out << std::endl;
}

bool GeneticAlgorithm::CheckData()
{
	for(int _class = 0; _class < classes_count; ++_class)
	{
		if(hours_for_classes[_class] <= 0 || hours_for_classes[_class] > days * hours_per_day)
			return false;

		int class_hours = 0;

		for(int _teacher = 0; _teacher < teachers_count; ++_teacher)
		{
			if(classes_curriculum[_class][_teacher] < 0)
				return false;

			class_hours += classes_curriculum[_class][_teacher];
		}

		if(class_hours != hours_for_classes[_class])
			return false;
	}

	for(int _teacher = 0; _teacher < teachers_count; ++_teacher)
	{
		unsigned int teacher_hours = 0;

		for(unsigned int i = 0; i < fixed_hours[_teacher].size(); ++i)
		{
			if(fixed_hours[_teacher][i].first < 0 || fixed_hours[_teacher][i].first >= days
				|| fixed_hours[_teacher][i].second < 0 || fixed_hours[_teacher][i].second >= hours_per_day)
				return false;
		}

		for(int _class = 0; _class < classes_count; ++_class)
		{
			teacher_hours += classes_curriculum[_class][_teacher];
		}

		if(teacher_hours + fixed_hours[_teacher].size() > days * hours_per_day)
			return false;
	}

	return true;
}