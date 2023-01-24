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
        // getline(cin, student.name);
        // getline(cin, student.surname);
        cin >> student.name >> student.surname >> student.day >> student.month >> student.year;
        --N;
    }

    int M;
    cin >> M;
    while (M)
    {
        string request;
        int number;
        cin >> request >> number;

        if (request == "name")
        {
            cout << students[number - 1].name << ' ' << students[number - 1].surname;
            cout << endl;
        }
        else if (request == "date")
        {
            cout << students[number - 1].day << '.'
                 << students[number - 1].month << '.'
                 << students[number - 1].year << '.';
            cout << endl;
        }
        else
        {
            cout << "bad request" << endl;
        }

        --M;
    }

    return 0;
}