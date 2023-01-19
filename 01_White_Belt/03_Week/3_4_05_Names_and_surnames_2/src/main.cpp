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

	string GetFullNameWithHistory(int year) {
		// получить все имена и фамилии по состоянию на конец года year
		string rezult;

		string first_name = GetNameWithHistory(year, firstNames);
		string last_name = GetNameWithHistory(year, lastNames);

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

	string GetNameWithHistory(int _year, map<int, string> _names) {
		string rezult;
		vector<string> names;

		for (const auto &item : _names) {
			if (item.first <= _year) {
				names.push_back(item.second);
				if (names[names.size() - 1] == names[names.size() - 2]) {
					names.pop_back();
				}
			}
		}

		if (names.size()) {

			//int d1 = names.size();////
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

	string getNameForYear(int _year, map<int, string> _names) {
		int __year;
		for (const auto &item : _names) {
			if (item.first <= _year) {
				__year = item.first;
			}
		}
		return _names[__year];
	}
}
;

int main() {
	Person person;
	/*
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
	 */

	person.ChangeFirstName(1965, "Polina");
	person.ChangeLastName(1967, "Sergeeva");
	for (int year : { 1900, 1965, 1990 }) {
		cout << person.GetFullNameWithHistory(year) << endl;
	}

	person.ChangeFirstName(1970, "Appolinaria");
	for (int year : { 1969, 1970 }) {
		cout << person.GetFullNameWithHistory(year) << endl;
	}

	person.ChangeLastName(1968, "Volkova");
	for (int year : { 1969, 1970 }) {
		cout << person.GetFullNameWithHistory(year) << endl;
	}

	person.ChangeFirstName(1990, "Polina");
	person.ChangeLastName(1990, "Volkova-Sergeeva");
	cout << person.GetFullNameWithHistory(1990) << endl;

	person.ChangeFirstName(1966, "Pauline");
	cout << person.GetFullNameWithHistory(1966) << endl;

	person.ChangeLastName(1960, "Sergeeva");
	for (int year : { 1960, 1967 }) {
		cout << person.GetFullNameWithHistory(year) << endl;
	}

	person.ChangeLastName(1961, "Ivanova");
	cout << person.GetFullNameWithHistory(1967) << endl;

	return 0;
}
