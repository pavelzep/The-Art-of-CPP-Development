#include <algorithm>
#include <iostream>
#include <string>
#include <vector>


#define TEST_ON

#ifdef TEST_ON
#include "test_runner.h"



#define BUG1
// #define BUG2
// #define BUG3
// #define BUG4
// #define BUG5
// #define BUG6

void Test1();
void Test2();
void Test3();
void Test4();
void Test5();
void Test6();
void Test_All();


#endif





using namespace std;

enum class Gender {
    FEMALE,
    MALE
};

struct Person {
    int age;
    Gender gender;
    bool is_employed;
};

bool operator==(const Person& lhs, const Person& rhs) {
    return lhs.age == rhs.age
        && lhs.gender == rhs.gender
        && lhs.is_employed == rhs.is_employed;
}

ostream& operator<<(ostream& stream, const Person& person) {
    return stream << "Person(age=" << person.age
        << ", gender=" << static_cast<int>(person.gender)
        << ", is_employed=" << boolalpha << person.is_employed << ")";
}

struct AgeStats {
    int total;
    int females;
    int males;
    int employed_females;
    int unemployed_females;
    int employed_males;
    int unemployed_males;
};

template <typename InputIt>
int ComputeMedianAge(InputIt range_begin, InputIt range_end) {
#ifndef BUG1
    if (range_begin == range_end) {
        return 0;
    }
#endif
    vector<typename iterator_traits<InputIt>::value_type> range_copy(
        range_begin,
        range_end
    );

#ifndef BUG2
    auto middle = begin(range_copy) + range_copy.size() / 2;
#else 
    auto middle = begin(range_copy) + (range_copy.size() + 1) / 2;
#endif
    nth_element(
        begin(range_copy), middle, end(range_copy),
        [](const Person& lhs, const Person& rhs) {
            return lhs.age < rhs.age;
        }
    );
    return middle->age;
}

vector<Person> ReadPersons(istream& in_stream = cin) {
    int person_count;
    in_stream >> person_count;
    vector<Person> persons;
    persons.reserve(person_count);
    for (int i = 0; i < person_count; ++i) {
#ifdef BUG3
        int age, is_employed, gender;
        cin >> age >> is_employed >> gender;
#else 
        int age, gender, is_employed;
        cin >> age >> gender >> is_employed;
#endif
        Person person{
            age,
            static_cast<Gender>(gender),
        #ifndef BUG4	
                is_employed == 1
        #else 
                is_employed == 0
        #endif
        };
        persons.push_back(person);
    }
    return persons;
}

AgeStats ComputeStats(vector<Person> persons) {
    //                 persons
    //                |       |
    //          females        males
    //         |       |      |     |
    //      empl.  unempl. empl.   unempl.

    auto females_end = partition(
        begin(persons), end(persons),
        [](const Person& p) {
            return p.gender == Gender::FEMALE;
        }
    );
    auto employed_females_end = partition(
        begin(persons), females_end,
        [](const Person& p) {
            return p.is_employed;
        }
    );
    auto employed_males_end = partition(
        females_end, end(persons),
        [](const Person& p) {
            return p.is_employed;
        }
    );

    return {
         ComputeMedianAge(begin(persons), end(persons)),
         ComputeMedianAge(begin(persons), females_end),
         ComputeMedianAge(females_end, end(persons)),
         ComputeMedianAge(begin(persons),  employed_females_end),
         ComputeMedianAge(employed_females_end, females_end),
  #ifndef BUG5
         ComputeMedianAge(females_end, employed_males_end),
  #else
         ComputeMedianAge(employed_males_end, females_end),
  #endif
         ComputeMedianAge(employed_males_end, end(persons))
    };
}

void PrintStats(const AgeStats& stats,
    ostream& out_stream = cout) {
    out_stream << "Median age = "
        << stats.total << endl

#ifndef BUG6
        << "Median age for females = "
        << stats.females << endl
        << "Median age for males = "
        << stats.males << endl
        << "Median age for employed females = "
        << stats.employed_females << endl
        << "Median age for unemployed females = "
        << stats.unemployed_females << endl
        << "Median age for employed males = "
        << stats.employed_males << endl
        << "Median age for unemployed males = "
        << stats.unemployed_males << endl;
#else
        << "Median age for males = "
        << stats.males << endl
        << "Median age for females = "
        << stats.females << endl
        << "Median age for unemployed females = "
        << stats.unemployed_females << endl
        << "Median age for employed females = "
        << stats.employed_females << endl
        << "Median age for unemployed males = "
        << stats.unemployed_males << endl;
    << "Median age for employed males = "
        << stats.employed_males << endl
#endif
}

#ifdef TEST_ON
void Test1() {

    // vector<Person> __persons{
    //     {25, Gender::FEMALE, true},
    //     {11, Gender::MALE, true},
    //     {78, Gender::MALE, false},
    //     {44, Gender::FEMALE, false},
    //     {66, Gender::FEMALE, false},
    //     {14, Gender::MALE, true},
    //     {29, Gender::FEMALE, true},
    // };

    {

        vector<Person> _persons{{78, Gender::MALE, false}};
        ASSERT_EQUAL(ComputeMedianAge(_persons.begin(), _persons.begin()), 0);
    }
}

void Test2() {

}
void Test3() {

}
void Test4() {

}
void Test5() {

}
void Test6() {

}

void Test_All() {
    TestRunner tr;


    RUN_TEST(tr, Test1);
    RUN_TEST(tr, Test2);
    RUN_TEST(tr, Test3);
    RUN_TEST(tr, Test4);
    RUN_TEST(tr, Test5);
    RUN_TEST(tr, Test6);


}
#endif

int main() {

#ifdef TEST_ON
    Test_All();
#else
    PrintStats(ComputeStats(ReadPersons()));
#endif
    return 0;
}



