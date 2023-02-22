#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
    os << "{";
    bool first = true;
    for (const auto& x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
    os << "{";
    bool first = true;
    for (const auto& x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
    os << "{";
    bool first = true;
    for (const auto& kv : m) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << kv.first << ": " << kv.second;
    }
    return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
    if (t != u) {
        ostringstream os;
        os << "Assertion failed: " << t << " != " << u;
        if (!hint.empty()) {
            os << " hint: " << hint;
        }
        throw runtime_error(os.str());
    }
}

void Assert(bool b, const string& hint) {
    AssertEqual(b, true, hint);
}

class TestRunner {
public:
    template <class TestFunc>
    void RunTest(TestFunc func, const string& test_name) {
        try {
            func();
            cerr << test_name << " OK" << endl;
        }
        catch (exception& e) {
            ++fail_count;
            cerr << test_name << " fail: " << e.what() << endl;
        }
        catch (...) {
            ++fail_count;
            cerr << "Unknown exception caught" << endl;
        }
    }

    ~TestRunner() {
        if (fail_count > 0) {
            cerr << fail_count << " unit tests failed. Terminate" << endl;
            exit(1);
        }
    }

private:
    int fail_count = 0;
};
/*
class Person {
public:
    // Вы можете вставлять сюда различные реализации класса,
    // чтобы проверить, что ваши тесты пропускают корректный код
    // и ловят некорректный
    void ChangeFirstName(int year, const string& first_name) {
    }
    void ChangeLastName(int year, const string& last_name) {
    }
    string GetFullName(int year) {
    }
};
*/
class Person {
public:
    void ChangeFirstName(int year, const string& first_name) {
        firstNames[year] = first_name;
    }
    void ChangeLastName(int year, const string& last_name) {
        lastNames[year] = last_name;
    }

    string GetFullName(int year) {
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

private:
    map<int, string> firstNames;
    map<int, string> lastNames;
    string getNameForYear(int _year, map<int, string> _names) {
        int __year;
        for (const auto& item : _names) {
            if (item.first <= _year) {
                __year = item.first;
            }
        }
        return _names[__year];
    }
};

void test_empty() {
    Person person;
    AssertEqual(person.GetFullName(1999), "Incognito", "empty don t return 'Incognito'");
    AssertEqual(person.GetFullName(1), "Incognito", "empty don t return 'Incognito'");
    AssertEqual(person.GetFullName(-999999), "Incognito", "empty don t return 'Incognito'");
    AssertEqual(person.GetFullName(0), "Incognito", "empty don t return 'Incognito'");
}

void add_name_to_empty() {
    { Person person;
    person.ChangeFirstName(1, "a");
    AssertEqual(person.GetFullName(1), "a with unknown last name", "name for 1 not 'a with unknown last name'");
    AssertEqual(person.GetFullName(0), "Incognito", "name for 0 not 'Incognito'");
    AssertEqual(person.GetFullName(-99999), "Incognito", "name for -99999 not 'Incognito'");
    AssertEqual(person.GetFullName(2), "a with unknown last name", "name for 2 not 'a with unknown last name'");
    AssertEqual(person.GetFullName(999999), "a with unknown last name", "name for 999999 not 'a with unknown last name'");
    }

    { Person person;
    person.ChangeFirstName(-99999, "b");
    AssertEqual(person.GetFullName(-199999), "Incognito", "name for -199999 not 'Incognito'");
    AssertEqual(person.GetFullName(-99999), "b with unknown last name", "name for -99999 not 'b with unknown last name'");
    AssertEqual(person.GetFullName(-9), "b with unknown last name", "name for -9 not 'b with unknown last name'");
    AssertEqual(person.GetFullName(99999), "b with unknown last name", "name for 99999 not 'b with unknown last name'");
    }


}

void change_name() {

    Person person;

    person.ChangeFirstName(-99999, "b");

    person.ChangeFirstName(999, "c");
    AssertEqual(person.GetFullName(-99999), "b with unknown last name", "name for -99999 not 'b with unknown last name'");
    AssertEqual(person.GetFullName(-9), "b with unknown last name", "name for -9 not 'b with unknown last name'");
    AssertEqual(person.GetFullName(99999), "c with unknown last name", "name for 99999 not 'c with unknown last name'");





    

}


void TestAll() {
    TestRunner runner;


    runner.RunTest(test_empty, "test_empty");
    runner.RunTest(add_name_to_empty, "add_name_to_empty");
    runner.RunTest(change_name, "change_name");





}


int main() {

    // добавьте сюда свои тесты
    TestAll();


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
