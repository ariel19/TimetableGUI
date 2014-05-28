#include "stdafx.h"
#include "GeneticAlgorithmWrapper.h"

using System::IntPtr;
using System::Runtime::InteropServices::Marshal;
using namespace System::Windows::Forms;

// TODO: probably will need to clean instance before reading file!!!!!!
GeneticAlgorithmWrapper::GeneticAlgorithmWrapper(void) {
	
	teachers = gcnew List<String^>;
	classes = gcnew List<Byte>;
	hours_for_classes = gcnew List<int>;
	classes_curriculum = gcnew List<List<int>^>;
	fixed_hours = gcnew List<List<KeyValuePair<int, int>>^>;
	population_size = 100;

	__classes_curriculum = gcnew List<KeyValuePair<Byte, KeyValuePair<String ^, int>>>;
	__fixed_hours = gcnew List<KeyValuePair<String ^, KeyValuePair<String ^, int>>>;

	prepared_data = false;

	days_num = gcnew Dictionary<String ^, int>();
	days_num->Add("Monday", 1);
	days_num->Add("Tuesday", 2);
	days_num->Add("Wednesday", 3);
	days_num->Add("Thursday", 4);
	days_num->Add("Friday", 5);

	/// =============================
	/// for testing purposes
	/*
	teachers->Add("Coldwind");
	classes->Add(1);
	hours_for_classes->Add(5);
	List<int> ^ t = gcnew List<int>;
	t->Add(10);
	classes_curriculum->Add(t);
	List<KeyValuePair<int, int>>^ t2 = gcnew List<KeyValuePair<int, int>>;
	t2->Add(KeyValuePair<int, int>(5, 5));
	fixed_hours->Add(t2);
	*/
	/// for testing purposes
	/// =============================
}

void GeneticAlgorithmWrapper::CreateInstance(/*List<String^> ^_t, List<Byte> ^_c, List<int> ^_hpw, List<List<int>^> ^_cc, List<List<KeyValuePair<int, int>>^> ^_fh*/) {
	std::vector<std::string> t;
	std::vector<char> c;
	std::vector<int> h4c;
	std::vector<std::vector<int>> cc;
	std::vector<std::vector<std::pair<int, int>>> fh;

	if (!prepared_data)
		convert_to_input();

	// convert teachers
	for each (String^ elem in teachers) {
		IntPtr ip = Marshal::StringToHGlobalAnsi(elem);
		std::string outString = static_cast<const char*>(ip.ToPointer());
		Marshal::FreeHGlobal(ip);
		t.push_back(outString);
	}

	// convert classes
	for each (Byte elem in classes)
		c.push_back(elem);

	// convert hours for classes
	for each (int elem in hours_for_classes)
		h4c.push_back(elem);
	
	// convert cc
	for each (List<int> ^l in classes_curriculum) {
		std::vector<int> v;
		for each(int val in l)
			v.push_back(val);
		cc.push_back(v);
	}

	// convert fixed hours
	for each (List<KeyValuePair<int, int>> ^l in fixed_hours) {
		std::vector<std::pair<int, int>> v;
		for each (KeyValuePair<int, int> p in l) {
			std::pair<int, int> _p(p.Key, p.Value);
			v.push_back(_p);
		}
		fh.push_back(v);
	}
	
	ga = new GeneticAlgorithm(t, c, h4c, cc, fh, population_size);
	if(!ga->CreateTimetable(1000, 10, 1, 0.5, 3, 0.95)) {
		MessageBox::Show("Incorrect input data", "Incorrect data", MessageBoxButtons::OK);
		return;
	}
}

String ^ GeneticAlgorithmWrapper::make_conversion() {
	convert_to_input();
	String ^s;
	
	// convert teachers
	s = (teachers->Count).ToString() + Environment::NewLine;

	for each (String^ elem in teachers)
		s += elem + Environment::NewLine;

	// convert classes
	s += (classes->Count).ToString() + Environment::NewLine;

	for each (Byte elem in classes)
		s += elem + Environment::NewLine;

	// convert hours for classes
	for each (int elem in hours_for_classes)
		s += elem + Environment::NewLine;
	
	// convert cc

	for each (List<int> ^l in classes_curriculum)
		for each(int val in l)
			s += val + Environment::NewLine;

	// convert fixed hours
	for each (List<KeyValuePair<int, int>> ^l in fixed_hours) {
		s += (l->Count).ToString() + Environment::NewLine;
		for each (KeyValuePair<int, int> p in l)
			s += p.Key + " " + Environment::NewLine;
	}

	return s;
}

bool GeneticAlgorithmWrapper::add_teacher(String ^t) {
	if (teachers->Contains(t))
		return false;
	Console::WriteLine("Add teacher: {0}", t);
	teachers->Add(t);
	return true;
}

bool GeneticAlgorithmWrapper::add_classes(Byte c) {
	if (classes->Contains(c))
		return false;
	Console::WriteLine("Add class: {0}", c);
	classes->Add(c);
	return true;
}

void GeneticAlgorithmWrapper::add_hpc(int hpc) {
	Console::WriteLine("Add Hours per class: {0}", hpc);
	hours_for_classes->Add(hpc);
}

bool GeneticAlgorithmWrapper::add_classes_curriculum(KeyValuePair<Byte, KeyValuePair<String ^, int>> d) {
	for each (KeyValuePair<Byte, KeyValuePair<String ^, int>> _d in __classes_curriculum) {
		if (d.Key == _d.Key && d.Value.Key == _d.Value.Key)
			return false;
	}
	Console::WriteLine("Add classes curriculum: {0}: {1} {2}", d.Key, d.Value.Key, d.Value.Value);
	__classes_curriculum->Add(d);
	return true;
}

bool GeneticAlgorithmWrapper::add_fixed_hours(KeyValuePair<String ^, KeyValuePair<String ^, int>> d) {
	if (__fixed_hours->Contains(d))
		return false;
	Console::WriteLine("Add fixed hours: {0}: {1} {2}", d.Key, d.Value.Key, d.Value.Value);
	__fixed_hours->Add(d);
	return true;
}

void GeneticAlgorithmWrapper::add_classes_curriculum(List<int> ^l) {
	classes_curriculum->Add(l);
}

void GeneticAlgorithmWrapper::add_fixed_hours(List<KeyValuePair<int, int>> ^l) {
	fixed_hours->Add(l);
}

void GeneticAlgorithmWrapper::convert_to_input() {
	Dictionary<String ^, int> ^__cc = gcnew Dictionary<String ^, int>;
	Dictionary<Byte, int> ^ __bi = gcnew Dictionary<Byte, int>;
	int i = 0, val = 0, j, 
		_teachers = teachers->Count;
	array<int> ^int_array = gcnew array<int>(_teachers);

	// CLASSES_CURRICULUM

	// fill array with zeros
	for (i = 0; i < _teachers; ++i)
		int_array[i] = 0;

	i = 0;
	// convert classes id : bytes -> int in List
	for each (Byte n in classes) {
		Console::WriteLine("bytes->int {0} : {1}", n, i);
		__bi->Add(n, i++);
		classes_curriculum->Add(gcnew List<int>(int_array));
	}

	i = 0;
	// convert int -> teacher's names
	for each (String ^name in teachers) {
		Console::WriteLine("string->int {0} : {1}", name, i);
		__cc->Add(name, i++);
	}

	//int size = classes->Count;
	for each (KeyValuePair<Byte, KeyValuePair<String ^, int>> d in __classes_curriculum) {
		Console::WriteLine("create a classes_curriculum class {0} = {1}: {2}", d.Key, d.Value.Key, d.Value.Value);

		classes_curriculum[__bi[d.Key]][__cc[d.Value.Key]] = d.Value.Value;
	}

	// FIXED HOURS
	// reserve space for all teachers
	for (i = 0; i < _teachers; ++i)
		fixed_hours->Add(gcnew List<KeyValuePair<int, int>>);
	
	for each  (KeyValuePair<String ^, KeyValuePair<String ^, int>> d in __fixed_hours) {
		Console::WriteLine("create a fixed_hours {0} = {1}: {2}", d.Key, d.Value.Key, d.Value.Value);

		fixed_hours[__cc[d.Key]]->Add(KeyValuePair<int, int>(days_num[d.Value.Key] - 1, d.Value.Value - 1));
	}

	delete __bi;
	delete __cc;
}

// TODO: add exception throwing
String ^ GeneticAlgorithmWrapper::num_to_day(int i) {
	for each (KeyValuePair<String ^, int> dn in days_num){
		if (dn.Value == i)
			return dn.Key;
	}
	return "FUCK";
}