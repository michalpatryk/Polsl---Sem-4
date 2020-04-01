#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <cstdlib>
#include <ctime>

std::ostream& operator<<(std::ostream& s, const std::list<std::string>& str)
{
	for (const auto& e : str)
	{
		s << e << std::endl;
	}
	return s;
}

std::ostream& operator<<(std::ostream& s, const std::multimap<float, int>& map)
{
	for (const auto& e : map)
	{
		s << e.second << ' ' << e.first << std::endl;
	}
	return s;
}

//operator w celu łatwiejszej implementacji klasy student_map
std::ostream& operator<<(std::ostream& s, const std::map<std::string, std::multimap<float, int>>& map)
{
	for (const auto& e : map)
	{
		std::cout << "Ocena, Waga" << std::endl;
		s << e.first << '\n' << e.second << std::endl;
	}
	return s;
}


class student_map
{
	std::map<std::string, std::multimap<float, int>> my_map;
public:
	student_map(std::map<std::string, std::multimap<float, int>> s) :my_map(s) {}

	void noteInput(std::string name, float weight, int note) { my_map[name].insert({weight, note }); }

	float noteAverage(std::string name)
	{
		if (my_map.count(name)) {
			float w = 0;
			int n = 0;
			for (auto& i : my_map[name]) {
				w += i.first;
				n += i.second * i.first;
			}
			return n / w;
		}
		else {
			std::cout << "Student not found" << std::endl;
			return 0;
		}
	}

	void assignStudent(std::string name, std::unordered_multimap<float, int> map)
	{
		for (auto& x : map)
		{
			my_map[name].insert(x);
		}
	}

	std::unordered_set<float> averageSet()
	{
		std::unordered_set<float> ts;
		for (auto& x : my_map)
		{
			ts.insert(this->noteAverage(x.first));
		}
		return ts;
	}

	void mapOutput()
	{
		std::cout << my_map;
	}
};

int main()
{
	srand(time(NULL));

	std::vector<std::string> students = { "Aaa", "Bbb", "Ccc", "Ddd", "Eee" };

	std::map<std::string, std::multimap<float, int>> map;
	for (int i = 0; i < 5; i++)
	{
		map[students[i]] = {};
	}

	student_map stdnt_map(map);
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			stdnt_map.noteInput(students[i], (float)(rand() % 50 + 10) / 10 , rand() % 4 + 1);	//note, weight
		}
	}
	std::unordered_multimap<float, int> nowy = { {2.2, 3}, {1.1, 4}, {3.3, 3}, {2.25, 5} };
	stdnt_map.assignStudent("Ddc", nowy);
	stdnt_map.mapOutput();
	std::unordered_set<float> ts = stdnt_map.averageSet();
	for (auto& x : ts)
	{
		std::cout << x << std::endl;
	}
	return 0;
}