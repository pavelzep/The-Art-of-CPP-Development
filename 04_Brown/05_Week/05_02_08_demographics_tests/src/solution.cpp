#include "test_runner.h"


// #include "bug0_good.cpp"

void Test1();
void Test2();
void Test3();
void Test4();
void Test5();
void Test6();

void Test_All();

void Test1() {
    vector<Person> _persons{ {78, Gender::MALE, false} };
    ASSERT_EQUAL(ComputeMedianAge(_persons.begin(), _persons.begin()), 0);
}
void Test2() {
    vector<Person> _persons{ {77, Gender::MALE, false},
                            {78, Gender::MALE, false},
                            {79, Gender::MALE, false} };
    ASSERT_EQUAL(ComputeMedianAge(_persons.begin(), _persons.end()), 78);
}
void Test3() {
    std::istringstream inbuf("1 23 0 1");
    vector<Person> _persons = ReadPersons(inbuf);
    Person   person = _persons[0];
    ASSERT_EQUAL(person.age, 23);
    ASSERT_EQUAL(static_cast<int>(person.gender), static_cast<int>(Gender::FEMALE));
    ASSERT_EQUAL(person.is_employed, true);
}
void Test4() {
    std::istringstream inbuf("1 23 0 1");
    vector<Person> _persons = ReadPersons(inbuf);
    Person   person = _persons[0];
    ASSERT_EQUAL(person.age, 23);
    ASSERT_EQUAL(static_cast<int>(person.gender), static_cast<int>(Gender::FEMALE));
    ASSERT_EQUAL(person.is_employed, true);
}
void Test5() {

    vector<Person> __persons{
        {25, Gender::FEMALE, true},
        {11, Gender::MALE, true},
        {78, Gender::MALE, false},
        {44, Gender::FEMALE, false},
        {66, Gender::FEMALE, false},
        {14, Gender::MALE, true},
        {29, Gender::FEMALE, true},
    };

    AgeStats as = ComputeStats(__persons);

}
void Test6() {
    vector<Person> __persons{
        {25, Gender::FEMALE, true},
        {11, Gender::MALE, true},
        {78, Gender::MALE, false},
        {44, Gender::FEMALE, false},
        {66, Gender::FEMALE, false},
        {14, Gender::MALE, true},
        {29, Gender::FEMALE, true},
    };

    ostringstream out;

    PrintStats(ComputeStats(__persons), out);

    string out_str = out.str();
    string correct_str = "\
Median age = 29\n\
Median age for females = 44\n\
Median age for males = 14\n\
Median age for employed females = 29\n\
Median age for unemployed females = 66\n\
Median age for employed males = 14\n\
Median age for unemployed males = 78\n\
";

    ASSERT_EQUAL(out_str, correct_str);
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

int main() {

    Test_All();
    return 0;

}
