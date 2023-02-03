// Реализуйте функции и методы классов и при необходимости добавьте свои
#include <string>
#include <map>
#include <iostream>
#include <exception>
#include <sstream>
#include <set>
#include <fstream>
#include <iomanip>

using namespace std;

class Date {
public:
    Date() {
        year = 0;
        month = 0;
        day = 0;
    }

    Date(const int new_year, const int new_month, const int new_day) {
        SetDay(new_day);
        SetMonth(new_month);
        SetYear(new_year);
    }

    void SetYear(const int new_year) {
        year = new_year;
    }
    void SetMonth(const int new_month) {
        if (new_month < 1 || new_month > 12) {
            throw out_of_range("Month value is invalid: " + to_string(new_month));
        }
        month = new_month;
    }
    void SetDay(const int new_day) {
        if (new_day < 1 || new_day > 31) {
            throw out_of_range("Day value is invalid: " + to_string(new_day));
        }
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
    else if (left.GetDay() < right.GetDay())
        return true;
    else
        return false;
}

/*
bool operator==(const Date& left, const Date& right) {
    if ((left.GetYear() == right.GetYear()) && (left.GetMonth() == right.GetMonth()) && (left.GetDay() == right.GetDay())) {
        return true;
    } else
        return false;
}
*/

ostream& operator<<(ostream& stream, const Date& date) {
    stream << setw(4) << setfill('0') << date.GetYear() << '-' << setw(2) << setfill('0') << date.GetMonth() << '-' << setw(2) << setfill('0') << date.GetDay();
    return stream;
}


iostream& operator>>(iostream& stream, Date& date) {
    int year;
    int month;
    int day;

    if (stream.peek() == '+')
        stream.ignore(1);

    stream >> year;

    if (stream.peek() != '-') {
        throw invalid_argument("Wrong date format");
    }
    stream.ignore(1);

    if (stream.peek() == '+')
        stream.ignore(1);
    stream >> month;


    if (stream.peek() != '-') {
        throw invalid_argument("Wrong date format");
    }
    stream.ignore(1);

    if (stream.peek() == '+')
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
        if (base.count(date)) {
            base.at(date).insert(event);
        } else {
            base[date] = { event };
        }
    }

    bool DeleteDate(const Date& date) {
        int count = base.at(date).size();
        if (count) {
            base.erase(date);
            cout << "Deleted " << count << " events" << endl;
            return 1;
        } else {
            cout << "nothing was del" << endl;
            return 0;
        }
    }

    bool DeleteEvent(const Date& date, const string& event) {
        // если дата есть в базе событий
        if (base.count(date)) {
            if (event.empty()) {
                return DeleteDate(date);
            } else {
                if (base[date].count(event)) {
                    base[date].erase(event);
                    //если теперь множество событий для даты стало пустым, то удаляем пустое множество
                    if (base[date].size() == 0) {
                        base.erase(date);
                    }
                    cout << "Deleted successfully" << endl;
                    return 1;
                } else {
                    cout << "Event not found" << endl;
                    return 0;
                }
            }
            //если даты нет в базе событий
        } else {
            cout << "Event not found" << endl;
            return 0;
        }
    }

    const set<string>& Find(const Date& date) const {
        int count = base.count(date);
        if (count) {
            return base.at(date);
        } else {
            return {};
        }
    }

    void Print() const {
        for (const auto& item : base) {
            cout << item.first << " ";
            for (const auto& evt : item.second) {
                cout << evt << ' ';
            }
            cout << endl;
        }
    }

private:
    map<Date, set<string>> base;
};

struct Instruction {
    string instruction;
    Date date;
    string event;
};



bool ParsingCommand(const string& command, Instruction& instruction, Database& base) {

    if (command.empty()) {
        return false;
    }


    stringstream stream(command);
    stream >> instruction.instruction;
    string date_string;


    if (instruction.instruction == "Add") {

        stream >> date_string;
        stringstream date_stream(date_string);

        try {
            date_stream >> instruction.date;
        }
        catch (invalid_argument& ex) {
            cout << ex.what() << ": " << date_string << endl;
            return 0;
        }
        catch (out_of_range& ex) {
            cout << ex.what() << endl;
            return 0;
        }

        stream >> instruction.event;


        base.AddEvent(instruction.date, instruction.event);

    } else if (instruction.instruction == "Del") {
        stream >> date_string;
        stringstream date_stream(date_string);
        try {
            date_stream >> instruction.date;
        }
        catch (invalid_argument& ex) {
            cout << ex.what() << ": " << date_string;
            return 0;
        }
        catch (out_of_range& ex) {
            cout << ex.what() << endl;
            return 0;
        }

        stream >> instruction.event;

        base.DeleteEvent(instruction.date, instruction.event);
    } else if (instruction.instruction == "Find") {
        stream >> date_string;
        stringstream date_stream(date_string);
        try {
            date_stream >> instruction.date;
        }
        catch (invalid_argument& ex) {
            cout << ex.what() << ": " << date_string;
            return 0;
        }
        catch (out_of_range& ex) {
            cout << ex.what() << endl;
            return 0;
        }

        for (const auto& item : base.Find(instruction.date)) {
            cout << item << endl;
        };

    } else if (instruction.instruction == "Print") {
        base.Print();

    } else {
        cout << "Unknown command: " << instruction.instruction << endl;
        return false;
    }
    return true;
}

/*
bool RunCommand(Database& base, const Instruction& instruction) {

    if (instruction.instruction == "Add") {
    } else if (instruction.instruction == "Del") {
    } else if (instruction.instruction == "Find") {
    } else if (instruction.instruction == "Print") {
    }
    return true;
}
*/
int main() {
    Database db;

    ifstream input("test.txt");

    string command;
    while (getline(input, command)) {
        Instruction instruction;
        try {
            ParsingCommand(command, instruction, db);

        }
        catch (invalid_argument& except) {
            cout << except.what() << endl;
        }
       /* catch (exception& ex){

        }*/
    }


    return 0;
}