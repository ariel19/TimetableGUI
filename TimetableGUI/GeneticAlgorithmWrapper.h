#pragma once

using namespace System::Collections::Generic;
using namespace System;

#include "GeneticAlgorithm.h"

public ref class GeneticAlgorithmWrapper {
	void convert_to_input();
public:
	// layer between C++ and C++ / CLI
	List<String^> ^teachers;
	List<Byte> ^classes;
	List<int> ^hours_for_classes;
	List<List<int>^> ^classes_curriculum;
	List<List<KeyValuePair<int, int>>^> ^fixed_hours;

	// structures for simplify access to data
	List<KeyValuePair<String ^, KeyValuePair<String ^, int>>> ^__fixed_hours;
	List<KeyValuePair<Byte, KeyValuePair<String ^, int>>> ^__classes_curriculum;

	// day numbers
	Dictionary<String ^, int> ^days_num;

	int population_size;

	bool prepared_data;

	static GeneticAlgorithm* ga;

	GeneticAlgorithmWrapper(void);

	void CreateInstance(/*List<String^> ^_t, List<Byte> ^_c, List<int> ^_hpw, List<List<int>^> ^_cc, List<List<KeyValuePair<int, int>>^> ^_fh*/);
	bool add_teacher(String ^);
	bool add_classes(Byte);
	void add_hpc(int);
	bool add_classes_curriculum(KeyValuePair<Byte, KeyValuePair<String ^, int>>);
	bool add_fixed_hours(KeyValuePair<String ^, KeyValuePair<String ^, int>>);

	void add_classes_curriculum(List<int> ^);
	void add_fixed_hours(List<KeyValuePair<int, int>> ^);

	String ^ make_conversion();
	String ^ num_to_day(int i);
};