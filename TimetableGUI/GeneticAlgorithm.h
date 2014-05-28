#pragma once
#include <string>
#include <vector>
#include <map>

class GeneticAlgorithm
{
private:
	char ****timetables; // [individual][teacher][day][hour]

	static int days;
	static int hours_per_day;
	static char fixed_hour_symbol;
	static char free_hour_symbol;
	static int max_last_lessons_count;
	static int max_iterations;

	int teachers_count;
	int classes_count;
	int population_size;

	// is finished
	volatile bool finished;

	std::vector<std::string> teachers;
	std::vector<char> classes;
	std::vector<int> hours_for_classes;
	std::vector<std::vector<int>> classes_curriculum;
	std::vector<std::vector<std::pair<int, int>>> fixed_hours;

	bool CheckData();
	void PrintTimetable(char ***timetable, std::ostream &out);
	void Initialize();
	void Crossover(std::vector<char***> &population, float probability, float infeasibilitiesWeight, 
		float didacticDissatisfactionWeight, float organizationalDissatisfactionWeight);
	std::vector<char***> Reproduction(float *fitness);
	void Succession(float *old_fitness, float *new_fitness, std::vector<char***> &new_population);
	void Filter(char ***individual);

	void ApplyMutationOfOrder(int individual, int mutationGenSize);
	void ApplyDayMutation(int individual);
	float * CalculateObjectiveFunction(char**** population, int p_size, float infeasibilitiesWeight, float didacticDissatisfactionWeight, 
		float organizationalDissatisfactionWeight);
	float CalculateLocalFitnessFunction(char**** population, int individual, int teacher, float didacticDissatisfactionWeight, 
		float organizationalDissatisfactionWeight);
	int CheckFeasibility(int individual, char**** population);
	float CheckDidacticRequirements(int individual, char**** population);
	float CheckLessonsDistribution(int teacher, int individual, char ****population);
	float CheckLessonsCirculation(int teacher, int individual, char **** population);
	float CheckOrganizationalRequirements(int individual, char**** population);
	int FindIndexOfClass(char c);
	int CalculateTeacherLessonsCount(int teacher);

public:
	GeneticAlgorithm(std::vector<std::string> _teachers, std::vector<char> _classes,
		std::vector<int> _hours_for_classes, std::vector<std::vector<int>> _classes_curriculum,
		std::vector<std::vector<std::pair<int, int>>> _fixed_hours, int _population_size);
	~GeneticAlgorithm();

	bool CreateTimetable(int stop, float infeasibilitiesWeight, float didacticDissatisfactionWeight, 
		float organizationalDissatisfactionWeight, int mutationGenSize, float crossoverProbability);
};