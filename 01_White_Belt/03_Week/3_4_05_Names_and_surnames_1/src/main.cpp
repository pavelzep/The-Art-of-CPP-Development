#include <iostream>
#include <map>
#include <vector>
#include <set> 
using namespace std;

class Person {
public:
	void ChangeFirstName(int year, const string &first_name) {
		// добавить факт изменения имени на first_name в год year
		firstNames[year] = first_name;
	}
	void ChangeLastName(int year, const string &last_name) {
		// добавить факт изменения фамилии на last_name в год year
		lastNames[year] = last_name;
	}

	string GetFullName(int year) {
		// получить имя и фамилию по состоянию на конец года year
		string rezult;

		string first_name = getNameForYear(year, firstNames);
		string last_name = getNameForYear(year, lastNames);

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

private:
	// приватные поля	
	map<int, string> firstNames;
	map<int, string> lastNames;

	string getNameForYear(int _year, map<int, string> _names) {
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
	Person person;

	person.ChangeFirstName(1965, "Polina");
	person.ChangeLastName(1967, "Sergeeva");
	for (int year : { 1900, 1965, 1990 }) {
		cout << person.GetFullName(year) << endl;
	}

	person.ChangeFirstName(1970, "Appolinaria");
	for (int year : { 1969, 1970 }) {
		cout << person.GetFullName(year) << endl;
	}

	person.ChangeLastName(1968, "Volkova");
	for (int year : { 1969, 1970 }) {
		cout << person.GetFullName(year) << endl;
	}

	return 0;
}
