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


bool GeneticAlgorithm::CreateTimetable(int stop, float infeasibilitiesWeight, float didacticDissatisfactionWeight, 
									   float organizationalDissatisfactionWeight, int mutationGenSize, float crossoverProbability)
{
	finished = false;

	if(!CheckData())
	{
		std::cout << "Bledne dane wejsciowe!" << std::endl;
		return false;
	}

	float min = std::numeric_limits<float>::max();
	char *** solution = new char **[teachers_count];
	for (int i = 0; i < teachers_count; i++)
	{
		solution[i] = new char*[days];
		for (int j = 0; j < days; j++)
		{
			solution[i][j] = new char[hours_per_day];
		}
	}
	int it = 0;
	int seed = time(NULL);
	while(it < stop)
	{
		std::cout << "New population cycle " << it << std::endl;
		srand(seed++);
		int iteration = 0;
		Initialize();
		for(int i = 0; i < population_size; ++i)
		{
			Filter(timetables[i]);
		}
		for(; it < stop; ++it)
		{
			std::cout << it << std::endl;
			float *initial_fitness = CalculateObjectiveFunction(timetables, population_size, infeasibilitiesWeight, didacticDissatisfactionWeight, 
				organizationalDissatisfactionWeight);
			std::vector<char***> new_population = Reproduction(initial_fitness);

			Crossover(new_population, crossoverProbability, infeasibilitiesWeight, 
				didacticDissatisfactionWeight, organizationalDissatisfactionWeight);

			float *new_fitness = CalculateObjectiveFunction(new_population.data(), new_population.size(), infeasibilitiesWeight, didacticDissatisfactionWeight, 
				organizationalDissatisfactionWeight);
			Succession(initial_fitness, new_fitness, new_population);

			delete [] initial_fitness;
			delete [] new_fitness;

			for (int individual = 0; individual < population_size; individual++)
			{
				ApplyMutationOfOrder(individual,mutationGenSize);
				ApplyDayMutation(individual);
				Filter(timetables[individual]);
			}
			float * results = CalculateObjectiveFunction(timetables, population_size, infeasibilitiesWeight, didacticDissatisfactionWeight, 
				organizationalDissatisfactionWeight);
			int idx = -1;
			for (int i = 0; i < population_size; i++)
			{
				if(results[i] < min)
				{
					min = results[i];
					idx = i;
				}
			}
			if(idx > -1)
			{
				for (int i = 0; i < teachers_count; i++)
				{
					for (int j = 0; j < days; j++)
					{
						for (int k = 0; k < hours_per_day; k++)
						{
							solution[i][j][k] = timetables[idx][i][j][k];
						}
					}
				}
				std::cout << "Actual minimum: " << min << std::endl;
				iteration = 0;
			}
			else
				iteration++;
			if(iteration > max_iterations)
				break;
		}
	}

	std::ofstream result;
	result.open("result.pout");
	std::cout << "Final minimum: " << std::endl << min << std::endl;
	std::cout << "Final solution:" << std::endl;
	PrintTimetable(solution, std::cout);
	PrintTimetable(solution, result);
	result.close();

	finished = true;

	return true;
}

void GeneticAlgorithm::Initialize()
{
	// Uzupelnienie fixed-hours
	for(int individual = 0; individual < population_size; ++individual)
		for(int teacher = 0; teacher < teachers_count; ++teacher)
			for(int day = 0; day < days; ++day)
				memset(timetables[individual][teacher][day], 0, hours_per_day);

	for(int individual = 0; individual < population_size; ++individual)
	{
		for(int teacher = 0; teacher < teachers_count; ++teacher)
		{
			for(unsigned int i = 0; i < fixed_hours[teacher].size(); ++i)
			{
				timetables[individual][teacher][fixed_hours[teacher][i].first][fixed_hours[teacher][i].second] = fixed_hour_symbol;
			}
		}
	}

	for(int individual = 0; individual < population_size; ++individual)
	{
		for(int _class = 0; _class < classes_count; ++_class)
		{
			for(int _teacher = 0; _teacher < teachers_count; _teacher++)
			{
				for(int i = 0; i < classes_curriculum[_class][_teacher]; ++i)
				{
					int day = rand() % days;
					int hour = rand() % hours_per_day;

					// Jeœli zajêty to szukamy kolejnego wolnego.
					while(timetables[individual][_teacher][day][hour] != 0)
					{
						hour++;
						if(hour == hours_per_day)
						{
							hour = 0;
							day++;
							if(day == days)
								day = 0;
						}
					}

					timetables[individual][_teacher][day][hour] = classes[_class];
				}
			}
		}

		// Oznaczanie wolnych godzin.
		for(int teacher = 0; teacher < teachers_count; ++teacher)
		{
			for(int day = 0; day < days; ++day)
			{
				for(int hour = 0; hour < hours_per_day; ++hour)
				{
					if(timetables[individual][teacher][day][hour] == 0)
						timetables[individual][teacher][day][hour] = free_hour_symbol;
				}
			}
		}
	}
}

std::vector<char***> GeneticAlgorithm::Reproduction(float *fitness)
{
	std::vector<char***> new_population;

	float avg = 0;
	for(int i = 0; i < population_size; ++i)
	{
		avg += fitness[i];
	}
	avg /= population_size;

	int count = 0;
	for(int i = 0; i < population_size; ++i)
	{
		if(fitness[i] < avg)
		{
			char ***tmt = new char**[teachers_count];
			for(int teacher = 0; teacher < teachers_count; ++teacher)
			{
				tmt[teacher] = new char*[days];

				for(int day = 0; day < days; ++day)
				{
					tmt[teacher][day] = new char[hours_per_day];

					for(int hour = 0; hour < hours_per_day; ++hour)
					{
						tmt[teacher][day][hour] = timetables[i][teacher][day][hour];
					}
				}
			}

			new_population.push_back(tmt);
			count++;
		}
	}

	return new_population;
}

void GeneticAlgorithm::Crossover(std::vector<char***> &population, float probability, float infeasibilitiesWeight, 
								 float didacticDissatisfactionWeight, float organizationalDissatisfactionWeight)
{
	int num_pairs = population.size() / 2;
	int size = population.size();

	std::vector<bool> free_pairs(size, true);

	// Losowanie par.
	for(int i = 0; i < num_pairs; ++i)
	{
		int x = rand() % size;
		int y = rand() % size;

		while(!free_pairs[x])
		{
			x++;
			if(x == size)
				x = 0;
		}

		free_pairs[x] = false;

		while(!free_pairs[y])
		{
			y++;
			if(y == size)
				y = 0;
		}

		free_pairs[y] = false;

		// Krzy¿uj.
		if(rand() % 100 < probability * 100)
		{
			std::vector<std::pair<int, float>> x_fitness;

			for(int teacher = 0; teacher < teachers_count; ++teacher)
			{
				float xf = CalculateLocalFitnessFunction(population.data(), x, teacher,  
					didacticDissatisfactionWeight, organizationalDissatisfactionWeight);

				std::pair<int, float> p_x(teacher, xf);

				x_fitness.push_back(p_x);
			}

			std::sort(x_fitness.begin(), x_fitness.end(), 
				[] (std::pair<int, float> &_x, std::pair<int, float> &_y) -> bool { return _x.second < _y.second; } );

			int k = teachers_count / 2;
			// TODO: wybieraæ k na podstawie œredniej.

			char ***timetable1 = new char**[teachers_count];
			char ***timetable2 = new char**[teachers_count];

			for(int t = 0; t < teachers_count; ++t)
			{
				if(t < k)
				{
					timetable1[x_fitness[t].first] = population[x][x_fitness[t].first];
					timetable2[x_fitness[t].first] = population[y][x_fitness[t].first];
				}
				else
				{
					timetable1[x_fitness[t].first] = population[y][x_fitness[t].first];
					timetable2[x_fitness[t].first] = population[x][x_fitness[t].first];
				}
			}

			delete [] population[x];
			delete [] population[y];

			population[x] = timetable1;
			population[y] = timetable2;
		}
	}
}

void GeneticAlgorithm::Succession(float *old_fitness, float *_new_fitness, std::vector<char***> &new_population)
{
	std::vector<float> new_fitness(_new_fitness, _new_fitness + new_population.size());

	while(!new_population.empty())
	{
		float *old_max = std::max_element(old_fitness, old_fitness + population_size);
		auto new_min = std::min_element(new_fitness.begin(), new_fitness.end());

		if(*old_max < *new_min)
			break;

		for(int teacher = 0; teacher < teachers_count; ++teacher)
		{
			for(int day = 0; day < days; ++day)
			{
				delete [] timetables[old_max - old_fitness][teacher][day];
			}

			delete [] timetables[old_max - old_fitness][teacher];
		}

		delete [] timetables[old_max - old_fitness];

		int new_pos = new_min - new_fitness.begin();
		timetables[old_max - old_fitness] = new_population[new_pos];
		new_fitness.erase(new_min);
		new_population.erase(new_population.begin() + new_pos);
	}

	for(unsigned int i = 0; i < new_population.size(); ++i)
	{
		for(int t = 0; t < teachers_count; ++t)
		{
			for(int d = 0; d < days; ++d)
			{
				delete [] new_population[i][t][d];
			}

			delete [] new_population[i][t];
		}

		delete [] new_population[i];
	}
}

void GeneticAlgorithm::ApplyMutationOfOrder(int individual, int mutationGenSize)
{
	int teacher, firstDay, secondDay, firstIndex, secondIndex;
	while(true)
	{
		teacher = rand()%teachers_count;
		firstDay = rand()%5;
		secondDay = rand()%5;
		if(secondDay == firstDay) secondDay = (secondDay + 1) % days;
		firstIndex = rand()%(hours_per_day - mutationGenSize);
		for (int i = 0; i < mutationGenSize && firstIndex + i < hours_per_day; i++)
		{
			if(timetables[individual][teacher][firstDay][i + firstIndex] == fixed_hour_symbol)
			{
				firstIndex += i+1;
				i = 0;
			}
		}
		if(hours_per_day - firstIndex < mutationGenSize) continue;
		secondIndex = rand()%(hours_per_day - mutationGenSize);
		for (int i = 0; i < mutationGenSize && secondIndex + i < hours_per_day; i++)
		{
			if(timetables[individual][teacher][secondDay][i + secondIndex] == fixed_hour_symbol)
			{
				secondIndex += i+1;
				i = 0;
			}
		}
		if(hours_per_day - secondIndex < mutationGenSize) continue;

		for (int i = 0; i < mutationGenSize; i++)
		{
			char tmp = timetables[individual][teacher][firstDay][i + firstIndex];
			timetables[individual][teacher][firstDay][i+firstIndex] = timetables[individual][teacher][secondDay][i + secondIndex];
			timetables[individual][teacher][secondDay][i + secondIndex] = tmp;
		}
		break;
	}
}

void GeneticAlgorithm::ApplyDayMutation(int individual)
{
	int teacher, firstDay, secondDay;
	teacher = rand()%teachers_count;
	firstDay = rand()%5;
	secondDay = rand()%5;
	if(secondDay == firstDay) secondDay = (secondDay + 1) % days;
	for (int i = 0; i < hours_per_day; i++)
	{
		char tmp = timetables[individual][teacher][firstDay][i];
		if(tmp != fixed_hour_symbol)
		{
			timetables[individual][teacher][firstDay][i] = timetables[individual][teacher][secondDay][i];
			timetables[individual][teacher][secondDay][i] = tmp;
		}
	}
}

void GeneticAlgorithm::Filter(char ***individual)
{
	// Step 0
	std::vector<std::vector<std::pair<int, std::vector<int>>>> over;
	std::vector<std::vector<int>> miss;

	for(int day = 0; day < days; ++day)
	{
		for(int hour = 0; hour < hours_per_day; ++hour)
		{
			int h = day * hours_per_day + hour;

			std::vector<std::pair<int, std::vector<int>>> h_over;

			std::vector<int> h_miss;
			std::vector<bool> missed(classes_count, true);

			for(int teacher = 0; teacher < teachers_count; ++teacher)
			{
				auto it = std::find(classes.begin(), classes.end(), individual[teacher][day][hour]);

				if(it == classes.end())
					continue;

				int iti = it - classes.begin();

				if(missed[iti] == true)
				{
					std::vector<int> vv;
					std::pair<int, std::vector<int>> over_class(iti, vv);
					h_over.push_back(over_class);

					missed[iti] = false;
				}

				auto oclass = std::find_if(h_over.begin(), h_over.end(), [&iti] (std::pair<int, std::vector<int>> x) -> bool { return x.first == iti; });
				oclass->second.push_back(teacher);
			}

			for(int i = 0; i < classes_count; ++i)
			{
				if(missed[i])
					h_miss.push_back(i);
			}

			std::remove_if(h_over.begin(), h_over.end(), [] (std::pair<int, std::vector<int>> x) -> bool { return x.second.size() == 1; });

			miss.push_back(h_miss);
			over.push_back(h_over);
		}
	}

	// Step 1
	while(true)
	{
		bool _continue = false;

		for(int h = 0; h < days * hours_per_day; ++h)
		{
			for(int k = 0; k < days * hours_per_day; ++k)
			{
				if(k != h)
				{
					for(int i = 0; i < miss[h].size(); ++i)
					{
						auto cj = std::find_if(over[k].begin(), over[k].end(), 
							[&miss, &h, &i] (std::pair<int, std::vector<int>> x) -> bool { return x.first == miss[h][i]; });

						if(cj != over[k].end())
						{
							for(int j = 0; j < miss[k].size(); ++j)
							{
								if(miss[k][j] != miss[h][i])
								{
									auto ci = std::find_if(over[h].begin(), over[h].end(), 
										[&miss, &k, &j] (std::pair<int, std::vector<int>> x) -> bool { return x.first == miss[k][j]; });

									if(ci != over[h].end())
									{
										for(int cir = 0; cir < ci->second.size(); ++cir)
										{
											for(int cjr = 0; cjr < cj->second.size(); ++cjr)
											{
												if(ci->second[cir] == cj->second[cjr])
												{
													int teacher = ci->second[cir];
													_continue = true;

													char tmp = individual[teacher][h / hours_per_day][h % hours_per_day];
													individual[teacher][h / hours_per_day][h % hours_per_day] = 
														individual[teacher][k / hours_per_day][k % hours_per_day];
													individual[teacher][k / hours_per_day][k % hours_per_day] = tmp;

													std::remove(miss[h].begin(), miss[h].end(), miss[h][i]);
													std::remove(miss[k].begin(), miss[k].end(), miss[k][j]);

													ci->second.erase(ci->second.begin() + cir);
													cj->second.erase(cj->second.begin() + cjr);

													std::remove_if(over[h].begin(), over[h].end(), 
														[] (std::pair<int, std::vector<int>> x) -> 
														bool { return x.second.size() == 1; });

													std::remove_if(over[k].begin(), over[k].end(), 
														[] (std::pair<int, std::vector<int>> x) -> 
														bool { return x.second.size() == 1; });

													goto eend1;
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}

eend1:
		if(!_continue)
			break;
	}

	// Step 2
	/*while(true)
	{
	bool _continue = false;

	for(int h = 0; h < days * hours_per_day; ++h)
	{
	for(int k = 0; k < days * hours_per_day; ++k)
	{
	if(k != h)
	{
	for(int i = 0; i < miss[k].size(); ++i)
	{
	auto ci = std::find_if(over[h].begin(), over[h].end(), 
	[&miss, &k, &i] (std::pair<int, std::vector<int>> x) -> bool { return x.first == miss[k][i]; });

	if(ci != over[h].end())
	{
	for(int cir = 0; cir < ci->second.size(); ++cir)
	{
	if(individual[ci->second[cir]][k / hours_per_day][k % hours_per_day] == free_hour_symbol)
	{
	_continue = true;

	char tmp = individual[ci->second[cir]][k / hours_per_day][k % hours_per_day];
	individual[ci->second[cir]][k / hours_per_day][k % hours_per_day] = 
	individual[ci->second[cir]][h / hours_per_day][h % hours_per_day];
	individual[ci->second[cir]][h / hours_per_day][h % hours_per_day] = tmp;

	std::remove(miss[k].begin(), miss[k].end(), miss[k][i]);
	ci->second.erase(ci->second.begin() + cir);

	std::remove_if(over[h].begin(), over[h].end(), 
	[] (std::pair<int, std::vector<int>> x) -> 
	bool { return x.second.size() == 1; });

	goto eend2;
	}
	}
	}
	}
	}
	}
	}

	eend2:
	if(!_continue)
	break;
	}*/
}