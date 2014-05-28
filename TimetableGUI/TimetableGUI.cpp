// TimetableGUI.cpp : main project file.

#include "stdafx.h"
#include "TimetableGUI.h"

#include <vector>
#include <iostream>

using namespace std;

using namespace TimetableGUI;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	// Enabling Windows XP visual effects before any controls are created
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 
	/*
	// TEST PURPOSES
		int n, m;

	cout << "Liczba nauczycieli: ";
	cin >> m;

	vector<string> teachers;
	teachers.reserve(m);

	for(int i = 0; i < m; ++i)
	{
		string s;
		cout << "Nazwa nauczyciela/przedmiotu " << i + 1 << ": ";
		cin >> s;
		teachers.push_back(s);
	}

	cout << endl << "Liczba klas: ";
	cin >> n;

	vector<char> classes;
	classes.reserve(n);

	for(int i = 0; i < n; ++i)
	{
		char c;
		cout << "Identyfikator klasy " << i + 1 << ": ";
		cin >> c;
		classes.push_back(c);
	}

	cout << endl;

	vector<int> hours_for_classes;
	hours_for_classes.reserve(n);

	for(int i = 0; i < n; ++i)
	{
		int x;
		cout << "Liczba godzin dla klasy " << classes[i] << ": ";
		cin >> x;
		hours_for_classes.push_back(x);
	}

	cout << endl;

	vector<vector<int>> classes_curriculum;
	classes_curriculum.reserve(n);

	for(int i = 0; i < n; ++i)
	{
		vector<int> x;
		x.reserve(m);

		for(int j = 0; j < m; ++j)
		{
			int y;
			cout << "Liczba godzin pracy nauczyciela " << teachers[j] << " w klasie " << classes[i] << ": ";
			cin >> y;
			x.push_back(y);
		}

		classes_curriculum.push_back(x);
	}

	vector<vector<pair<int, int>>> fixed_hours;

	for(int i = 0; i < m; ++i)
	{
		vector<pair<int, int>> fh;
		int x;
		cout << endl << "Liczba stalych godzin dla nauczyciela " << teachers[i] << ": ";
		cin >> x;

		for(int j = 0; j < x; ++j)
		{
			int y, z;
			cout << "Dzien i godzina dla nauczyciela " << teachers[i] << " i godziny " << j + 1 << ": ";
			cin >> y >> z;
			pair<int, int> pp(y - 1, z - 1);
			fh.push_back(pp);
		}

		fixed_hours.push_back(fh);
	}

	GeneticAlgorithm ga(teachers, classes, hours_for_classes, classes_curriculum, fixed_hours, 100);
	// z tym co wyjdzie trzeba jakoœ zjechaæ prawie do zera
	ga.CreateTimetable(1000, 10, 1, 0.5, 3, 0.95);

	*/
	// TEST PURPOSES

	// Create the main window and run it
	Application::Run(gcnew TTGUI());
	return 0;
}
