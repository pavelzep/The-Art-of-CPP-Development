#include <iostream>
#include <map>

using namespace std;

class Person {
public:
	void ChangeFirstName(int year, const string &first_name) {
		// добавить факт изменения имени на first_name в год year
		firstNames[year]=first_name;
	}
	void ChangeLastName(int year, const string &last_name) {
		// добавить факт изменения фамилии на last_name в год year
		lastNames[year]=last_name;
	}
	string GetFullName(int year) {
		// получить имя и фамилию по состоянию на конец года year
		string rezult;

		bool first_name_valid = firstNames.count(year);
		bool last_name_valid = lastNames.count(year);

		if(first_name_valid && last_name_valid){
			cout << firstNames[year] << ' ' << lastNames[year];

		}else if (!first_name_valid && last_name_valid){
			cout << lastNames[year]<< " with unknown first name";

		}else if(first_name_valid && !last_name_valid){

			cout << firstNames[year] << " with unknown last name";
		}else if(!first_name_valid && !last_name_valid){
			cout << "Incognito" ;
		}

		return rezult;
	}

private:

	map<int, string> firstNames;
	map<int, string> lastNames;
	// приватные поля
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
