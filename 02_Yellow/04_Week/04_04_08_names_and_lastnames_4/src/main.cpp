// Имена и фамилии — 4
// Решите задачу «Имена и фамилии — 1» более эффективно, использовав двоичный поиск в методе Person::GetFullName. Напомним условие задачи.
// Реализуйте класс для человека, поддерживающий историю изменений человеком своих фамилии и имени.

// class Person {
// public:
//   void ChangeFirstName(int year, const string& first_name) {
//     // добавить факт изменения имени на first_name в год year
//   }
//   void ChangeLastName(int year, const string& last_name) {
//     // добавить факт изменения фамилии на last_name в год year
//   }
//   string GetFullName(int year) {
//     // получить имя и фамилию по состоянию на конец года year
//     // с помощью двоичного поиска
//   }
// private:
//   // приватные поля
// };

// Считайте, что в каждый год может произойти не более одного изменения фамилии и не более одного изменения имени. 
// При этом с течением времени могут открываться всё новые факты из прошлого человека, поэтому года́ в последовательных 
// вызовах методов ChangeLastName и ChangeFirstName не обязаны возрастать.
// Гарантируется, что все имена и фамилии непусты.
// Строка, возвращаемая методом GetFullName, должна содержать разделённые одним пробелом имя и фамилию человека по состоянию на конец данного года.
// Если к данному году не случилось ни одного изменения фамилии и имени, верните строку "Incognito".
// Если к данному году случилось изменение фамилии, но не было ни одного изменения имени, верните "last_name with unknown first name".
// Если к данному году случилось изменение имени, но не было ни одного изменения фамилии, верните "first_name with unknown last name".

// Пример:
// Код:
// int main() {
//     Person person;
//     person.ChangeFirstName(1965, "Polina");
//     person.ChangeLastName(1967, "Sergeeva");
//     for (int year : {1900, 1965, 1990}) {
//         cout << person.GetFullName(year) << endl;
//     }
//     person.ChangeFirstName(1970, "Appolinaria");
//     for (int year : {1969, 1970}) {
//         cout << person.GetFullName(year) << endl;
//     }
//     person.ChangeLastName(1968, "Volkova");
//     for (int year : {1969, 1970}) {
//         cout << person.GetFullName(year) << endl;
//     }
//     return 0;
// }

// Вывод:
// Incognito
// Polina with unknown last name
// Polina Sergeeva
// Polina Sergeeva
// Appolinaria Sergeeva
// Polina Volkova
// Appolinaria Volkova


#include <iostream>
#include <map>
#include <vector>
#include <set> 
#include <algorithm>
using namespace std;

class Person {
public:
    void ChangeFirstName(int year, const string& first_name) {
        // добавить факт изменения имени на first_name в год year
        firstNames[year] = first_name;
    }
    void ChangeLastName(int year, const string& last_name) {
        // добавить факт изменения фамилии на last_name в год year
        lastNames[year] = last_name;
    }

    // string GetFullName(int year) {

    // }

    string GetFullName(int year) {
        // получить имя и фамилию по состоянию на конец года year
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
    // приватные поля	
    map<int, string> firstNames;
    map<int, string> lastNames;

    // string getNameForYear(int _year, map<int, string> _names) {
    //     int __year;
    //     for (const auto& item : _names) {
    //         if (item.first <= _year) {
    //             __year = item.first;
    //         }
    //     }
    //     return _names[__year];
    // }

    string getNameForYear(int _year, map<int, string>& _names) {

        auto low = _names.lower_bound(_year);

        if ((*low).first == _year) return (*low).second;

        if (low == _names.begin()) return "";

        return (*prev(low)).second;

    }
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
