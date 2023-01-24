#include <iostream>
#include <vector>

using namespace std;

struct Student
{
    string name;
    string surname;
    int day;
    int month;
    int year;
};

int main()
{
    int N;
    cin >> N;
    vector<Student> students;

    while (N)
    {
        Student student;
        getline(cin, student.name);
        getline(cin, student.surname);
        cin >> student.day >> student.month >> student.year;
        --N;
    }
    int M;
    cin >> M;
    while (M)
    {

        --M;
    }

    return 0;
}