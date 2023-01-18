#include <iostream>
#include <map>
#include <vector>
#include <set> 
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

	string GetFirstName(int year){
		if(firstNames.count(year)){
			return firstNames[year];	
		}
			else{

			}
	}



	string GetFullName(int year) {
		// получить имя и фамилию по состоянию на конец года year
		string rezult;

		int first_name_year = 0;
		int last_name_year = 0;

		for(const auto & item :firstNames){
			if(item.first <= year){
				first_name_year=item.first;
			}
		}

		for(const auto & item :lastNames){
			if(item.first <= year){
				last_name_year=item.first;
			}
		}



		bool first_name_valid = firstNames.count(first_name_year);
		bool last_name_valid = lastNames.count(last_name_year);

		if(first_name_valid && last_name_valid){
			cout << firstNames[first_name_year] << ' ' << lastNames[last_name_year];

		}else if (!first_name_valid && last_name_valid){
			cout << lastNames[last_name_year]<< " with unknown first name";

		}else if(first_name_valid && !last_name_valid){

			cout << firstNames[first_name_year] << " with unknown last name";
		}else if(!first_name_valid && !last_name_valid){
			cout << "Incognito" ;
		}

		return rezult;
	}




private:
	// приватные поля	
	map<int, string> firstNames;
	map<int, string> lastNames;
	
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
