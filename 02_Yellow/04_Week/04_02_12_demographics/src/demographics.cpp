#include "demographics.h"

#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

void PrintStats(vector<Person> persons) {
    cout << "Median age = " << ComputeMedianAge(persons.begin(), persons.end()) << endl;
    auto it = partition(persons.begin(), persons.end(), [persons](Person pers) {return pers.gender == Gender::FEMALE;});
    cout << "Median age for females = " << ComputeMedianAge(persons.begin(), it) << endl;
    cout << "Median age for males = " << ComputeMedianAge(it, persons.end()) << endl;
    auto it1 = partition(persons.begin(), it, [persons](Person pers) {return pers.is_employed == true;});
    cout << "Median age for employed females = " << ComputeMedianAge(persons.begin(), it1) << endl;
    cout << "Median age for unemployed females = " << ComputeMedianAge(it1, it) << endl;
    auto it2 = partition(it, persons.end(), [persons](Person pers) {return pers.is_employed == true;});
    cout << "Median age for employed males = " << ComputeMedianAge(it, it2) << endl;
    cout << "Median age for unemployed males = " << ComputeMedianAge(it2, persons.end()) << endl;
}
