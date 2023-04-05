#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Person {
public:
    Person(const string& name):Name(name) {

    }
    virtual void Walk(const string& destination) = 0;
    string Name;
};

class Student: public Person {
public:

    Student(const string& name, const string& favouriteSong): Person(name) {
        FavouriteSong = favouriteSong;
    }

    void Walk(const string& destination) override {
        cout << "Student: " << Name << " walks to: " << destination << endl;
        cout << "Student: " << Name << " sings a song: " << FavouriteSong << endl;
    }

    void Learn() {
        cout << "Student: " << Name << " learns" << endl;
    }

    void SingSong() {
        cout << "Student: " << Name << " sings a song: " << FavouriteSong << endl;
    }

private:
    string FavouriteSong;
};


class Teacher: public Person {
public:

    Teacher(const string& name, const string& subject):Person(name) {

        Subject = subject;
    }

    void Walk(const string& destination) override {
        cout << "Teacher: " << Name << " walks to: " << destination << endl;
    }

    void Teach() {
        cout << "Teacher: " << Name << " teaches: " << Subject << endl;
    }

private:
    string Subject;
};


class Policeman: public Person {
public:
    Policeman(const string& name):Person(name) {
    }

    void Check(Teacher& t) {
        cout << "Policeman: " << Name << " checks Teacher. Teacher's name is: " << t.Name << endl;
    }

    void Check(Student& s) {
        cout << "Policeman: " << Name << " checks Student. Student's name is: " << s.Name << endl;
    }

    void Check(Policeman& p) {
        cout << "Policeman: " << Name << " checks Policeman. Policeman's name is: " << p.Name << endl;
    }

    void Walk(const string& destination) override {
        cout << "Policeman: " << Name << " walks to: " << destination << endl;
    }
};


void VisitPlaces(Teacher& t, const vector<string>& places) {
    for (auto p : places) {
        t.Walk(p);
    }
}

void VisitPlaces(Student& s, const vector<string>& places) {
    for (auto p : places) {
        s.Walk(p);
    }
}

void VisitPlaces(Policeman& pol, const vector<string>& places) {
    for (auto p : places) {
        pol.Walk(p);
    }
}


int main() {
    Teacher t("Jim", "Math");
    Student s("Ann", "We will rock you");
    Policeman p("Bob");

    VisitPlaces(t, { "Moscow", "London" });
    p.Check(s);
    VisitPlaces(s, { "Moscow", "London" });
    return 0;
}