#include <iostream>
#include <map>
#include <vector>
#include <set> 
using namespace std;

class Person {
public:
	Person(const string &first_name, const string &last_name, int year) {
		firstNames[year] = first_name;
		lastNames[year] = last_name;
		year_of_birth = year;
	}
	void ChangeFirstName(int year, const string &first_name) {
		if(year < year_of_birth) return;
		firstNames[year] = first_name;
	}
	void ChangeLastName(int year, const string &last_name) {
		if(year < year_of_birth) return;
		lastNames[year] = last_name;
	}

	string GetFullName(int year) const {
		if(year < year_of_birth) return "No person";
		string first_name = getNameForYear(year, firstNames);
		string last_name = getNameForYear(year, lastNames);
		return BuildNameString(first_name, last_name);
	}

	string GetFullNameWithHistory(int year) const {
		if(year < year_of_birth) return "No person";
		string first_name = GetNameWithHistory(year, firstNames);
		string last_name = GetNameWithHistory(year, lastNames);
		return BuildNameString(first_name, last_name);
	}

private:

	int year_of_birth;
	map<int, string> firstNames;
	map<int, string> lastNames;

	string BuildNameString(const string &first_name, const string &last_name) const {
		string rezult;
		if (!first_name.empty() && !last_name.empty()) {
			rezult = first_name + " " + last_name;

		} else if (first_name.empty() && !last_name.empty()) {
			rezult = last_name + " with unknown first name";

		} else if (!first_name.empty() && last_name.empty()) {
			rezult = first_name + " with unknown last name";
		} else if (first_name.empty() && last_name.empty()) {
			rezult = "Incognito";
		}
		return rezult;
	}

	string GetNameWithHistory  (int _year, map<int, string> _names) const {
		vector<string> names;
		for (const auto &item : _names) {
			if (item.first <= _year
					&& (names.empty() || names.back() != item.second))
				names.push_back(item.second);
		}

		string rezult;
		if (names.size()) {
			rezult = names[names.size() - 1];
			names.pop_back();
			string prevNames;

			if (names.size()) {
				rezult += " (";
				while (names.size()) {
					prevNames += names[names.size() - 1];
					names.pop_back();
					if (names.size()) {
						prevNames += ", ";
					}
				}
				rezult += prevNames;
				rezult += ')';
			}
		}
		return rezult;
	}

	string getNameForYear (int _year, map<int, string> _names) const {
		int __year;
		for (const auto &item : _names) {
			if (item.first <= _year) {
				__year = item.first;
			}
		}
		return _names[__year];
	}
};

int main() {
	Person person("Polina", "Sergeeva", 1960);
	for (int year : { 1959, 1960 }) {
		cout << person.GetFullNameWithHistory(year) << endl;
	}

	person.ChangeFirstName(1965, "Appolinaria");
	person.ChangeLastName(1967, "Ivanova");
	for (int year : { 1965, 1967 }) {
		cout << person.GetFullNameWithHistory(year) << endl;
	}

	return 0;
}
