// Реализуйте функции и методы классов и при необходимости добавьте свои
#include <string>
#include <map>
#include <iostream>
#include <exception>
#include <sstream>
#include <set>
#include <fstream>

using namespace std;

class Date {
public:
    Date() {
        year = 0;
        month = 0;
        day = 0;
    }

    Date(const int new_year, const int new_month, const int new_day) {
        if (new_month < 1 && new_month > 12) {
            throw exception();
        }
        if (new_day < 1 && new_day > 31) {
            throw exception();
        }
        day = new_day;
        month = new_month;
        year = new_year;
    }

    void SetYear(const int new_year) {
        year = new_year;
    }
    void SetMonth(const int new_month) {
        month = new_month;
    }
    void SetDay(const int new_day) {
        day = new_day;
    }
    int GetYear() const {
        return year;
    }
    int GetMonth() const {
        return month;
    }
    int GetDay() const {
        return day;
    }

private:
    int year;
    int month;
    int day;
};

bool operator<(const Date& left, const Date& right) {
    if (left.GetYear() < right.GetYear())
        return true;
    else if (left.GetYear() > right.GetYear())
        return false;
    else if (left.GetMonth() < right.GetMonth())
        return true;
    else if (left.GetMonth() > right.GetMonth())
        return false;
    else if (left.GetDay() <= right.GetDay())
        return true;
    else
        return false;
}

bool operator==(const Date& left, const Date& right) {
    if ((left.GetYear() == right.GetYear()) && (left.GetMonth() == right.GetMonth()) && (left.GetDay() == right.GetDay())) {
        return true;
    } else
        return false;
}

ostream& operator<<(ostream& stream, const Date& date) {
    stream << date.GetYear() << '-' << date.GetMonth() << '-' << date.GetDay();
    return stream;
}


iostream& operator>>(iostream& stream, Date& date) {
    int year;
    int month;
    int day;
    stream >> year;
    if (stream.peek() != '-') {
        throw invalid_argument("wrong month format");
    }
    stream.ignore(1);

    stream >> month;
    if (stream.peek() != '-') {
        throw invalid_argument("wrong day formdat");
    }
    stream.ignore(1);

    stream >> day;

    date.SetYear(year);
    date.SetMonth(month);
    date.SetDay(day);

    return stream;
}
class Database {
public:
    void AddEvent(const Date& date, const string& event) {
        base[date] = event;
    }

    bool DeleteEvent(const Date& date, const string& event) {
        if (!event.empty()) {
            try {
                if (base.at(date) == event) {
                    base.erase(date);
                    cout << "ok" << endl;
                    return 1;
                }
            }
            catch (out_of_range& ex) {
                cout << ex.what() << "not ok" << endl;
                return 0;
            }
        } else {
            return DeleteDate(date);
        }
    }

    bool DeleteDate(const Date& date) {
        int c = base.count(date);
        while (base.count(date)) {
            base.erase(date);
        }
        cout << "was del " << c << " events";
        return 1;
    }

    set<string> Find(const Date& date) const {

        set<string> events;
        int c = base.count(date);
        while (base.count(date)) {
            events.insert(base.at(date));
        }
        return events;
    }

    void Print() const {
        for (const auto& item : base) {
            cout << item.first << ' ' << item.second;
        }
    }

private:
    map<Date, string> base;
};

struct Instruction {
    string instruction;
    Date date;
    string event;
};

bool ParsingCommand(const string& command, Instruction& instruction) {
    stringstream stream(command);
    stream >> instruction.instruction;

    if (instruction.instruction == "Add") {
        stream >> instruction.date;
        stream >> instruction.event;
    } else if (instruction.instruction == "Del") {
        stream >> instruction.date;
        stream >> instruction.event;
    } else if (instruction.instruction == "Find") {
        stream >> instruction.date;
    } else if (instruction.instruction == "Print") {

    } else {

    }
    return true;
}


bool RunCommand(Database& base, const Instruction& instruction) {

    if (instruction.instruction == "Add") {
        base.AddEvent(instruction.date, instruction.event);
    } else if (instruction.instruction == "Del") {
        base.DeleteEvent(instruction.date, instruction.event);
    } else if (instruction.instruction == "Find") {
        set<string> events = base.Find(instruction.date);
        for (const auto& item : events/*base.Find(instruction.date)*/) {
            cout << item << endl;
        };
    } else if (instruction.instruction == "Print") {
        base.Print();
    }

    return true;
}

int main() {
    Database db;

    ifstream input("test.txt");

    string command;
    while (getline(input, command)) {
        Instruction instruction;
        try {
            ParsingCommand(command, instruction);
        }
        catch (invalid_argument& except) {
            cout << except.what() << endl;
        }
        RunCommand(db, instruction);
    }


    return 0;
}