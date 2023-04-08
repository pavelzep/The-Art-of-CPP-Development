#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Person {
public:
    Person(const string& name, const string& type):Name(name), Type(type) {}
    virtual void Walk(const string& destination) const {
        cout << Type << ": " << Name << " walks to: " << destination << endl;
    }
    string Name;
    string Type;
};

class Student: public Person {
public:
    Student(const string& name, const string& favouriteSong): Person(name, "Student"), FavouriteSong(favouriteSong) {
    }

    void Walk(const string& destination) const override {
        Person::Walk(destination);
        SingSong();
    }

    void Learn() const {
        cout << Type << ": " << Name << " learns" << endl;
    }

    void SingSong() const {
        cout << Type << ": " << Name << " sings a song: " << FavouriteSong << endl;
    }

private:
    string FavouriteSong;
};


class Teacher: public Person {
public:
    Teacher(const string& name, const string& subject): Person(name, "Teacher"), Subject(subject) {}

    void Teach() const {
        cout << Type << ": " << Name << " teaches: " << Subject << endl;
    }

private:
    string Subject;
};


class Policeman: public Person {
public:
    Policeman(const string& name): Person(name, "Policeman") {}

    void Check(const Person& t) const {
        cout << Type << ": " << Name << " checks " << t.Type << ". " << t.Type << "'s name is: " << t.Name << endl;
    }

};

void VisitPlaces(const Person& p, const vector<string>& places) {
    for (auto pl : places) {
        p.Walk(pl);
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