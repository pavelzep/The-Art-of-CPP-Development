#include <string>
#include <map>
#include <iostream>
#include <exception>
#include <sstream>
#include <set>
#include <fstream>
#include <iomanip>
#include <vector>

using namespace std;

class Date {
public:
    Date() {
        year = 0;
        month = 0;
        day = 0;
    }

    void SetYear(const int new_year) {
        year = new_year;
    }
    void SetMonth(const int new_month) {
        if (new_month < 1 || new_month > 12) {
            throw out_of_range("Month value is invalid: " + to_string(new_month));
            return;
        }
        month = new_month;
    }
    void SetDay(const int new_day) {
        if (new_day < 1 || new_day > 31) {
            throw out_of_range("Day value is invalid: " + to_string(new_day));
            return;
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

ostream& operator<<(ostream& stream, const Date& date) {
    stream << setw(4) << setfill('0') << date.GetYear() << '-' << setw(2) << setfill('0') << date.GetMonth() << '-' << setw(2) << setfill('0') << date.GetDay();
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
        if (base.count(date) == 0) {
            cout << "Deleted " << '0' << " events" << endl;
            return 1;
        }
        int count = base.at(date).size();
        if (count) {
            base.erase(date);
            cout << "Deleted " << count << " events" << endl;
            return 1;
        } else {
            cout << "Deleted " << '0' << " events" << endl;
            return 1;
        }
    }

    bool DeleteEvent(const Date& date, const string& event) {
        if (event.empty()) {
            return DeleteDate(date);
        }

        if (base.count(date)) {
            if (base[date].count(event)) {
                base[date].erase(event);

                if (base[date].size() == 0) {
                    base.erase(date);
                }
                cout << "Deleted successfully" << endl;
                return 1;
            } else {
                cout << "Event not found" << endl;
                return 1;
            }
        } else {
            cout << "Event not found" << endl;
            return 1;
        }
    }

    const set<string> Find(const Date& date) const {
        int count = base.count(date);
        if (count) {
            return base.at(date);
        } else {
            set<string> set;
            return {};
        }
    }

    void Print() const {
        for (const auto& item : base) {
            for (const auto& evt : item.second) {
                cout << item.first << ' ' << evt << endl;
            }
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


int getNumfromString(string& str) {
    try {
       return stoi(str);
    }
    catch (invalid_argument&) {
        throw invalid_argument("Wrong date format: ");
        return -1;
    }

}

void cutString(string& str) {
    stringstream ss(str);
    int temp;
    ss >> temp;
    if(ss.peek()!='-'){
        throw invalid_argument("Wrong date format: ");
    }
    ss >> str;

}

Date ParsingDate(const string& dateString) {
    int year = -1;
    int month = -1;
    int day = -1;
    Date date;

    string temp_str = dateString;
    year = getNumfromString(temp_str);



















    date.SetYear(year);
    date.SetMonth(month);
    date.SetDay(day);
    return  date;
}

set<char> validSymbols = { '-','+','0','1','2','3','4','5','6','7','8','9' };
Date ParsingDate2(const string& dateString) {
    int year;
    int month;
    int day;

    stringstream date_stream(dateString);

    if (date_stream.peek() == '+')
        date_stream.ignore(1);

    if (!validSymbols.count(date_stream.peek())) {
        throw invalid_argument("Wrong date format: " + dateString);
    }
    date_stream >> year;

    if (date_stream.peek() != '-') {
        throw invalid_argument("Wrong date format: " + dateString);
    }
    date_stream.ignore(1);

    if (date_stream.peek() == '+')
        date_stream.ignore(1);

    if (!validSymbols.count(date_stream.peek())) {
        throw invalid_argument("Wrong date format: " + dateString);
    }
    date_stream >> month;


    if (date_stream.peek() != '-') {
        throw invalid_argument("Wrong date format: " + dateString);
    }
    date_stream.ignore(1);

    if (date_stream.peek() == '+')
        date_stream.ignore(1);

    if (!validSymbols.count(date_stream.peek())) {
        throw invalid_argument("Wrong date format: " + dateString);
    }
    date_stream >> day;

    if (date_stream.peek() > 0) {
        throw invalid_argument("Wrong date format: " + dateString);
    }

    Date date;
    date.SetYear(year);
    date.SetMonth(month);
    date.SetDay(day);
    return  date;
}


bool ParsingCommand(const string& command, Instruction& instruction, Database& base) {

    if (command.empty()) {
        return true;
    }

    stringstream stream(command);
    stream >> instruction.instruction;

    if (instruction.instruction == "Add" ||
        instruction.instruction == "Del" ||
        instruction.instruction == "Find") {

        string dateString;
        stream >> dateString;
        try {
            instruction.date = ParsingDate(dateString);
        }
        catch (invalid_argument& except) {
            cout << except.what() << endl;
            return false;
        }
        catch (out_of_range& except) {
            cout << except.what() << endl;
            return false;
        }
        if (instruction.instruction != "Find")
            stream >> instruction.event;

        return true;
    } else if (instruction.instruction == "Print") {
        return true;
    } else {
        throw domain_error("Unknown command: " + instruction.instruction);
        return false;
    }
}


void RunCommand(Database& base, const Instruction& instruction) {

    if (instruction.instruction == "Add") {
        base.AddEvent(instruction.date, instruction.event);
    } else if (instruction.instruction == "Del") {
        base.DeleteEvent(instruction.date, instruction.event);
    } else if (instruction.instruction == "Find") {
        for (const auto& item : base.Find(instruction.date)) {
            cout << item << endl;
        };
    } else if (instruction.instruction == "Print") {
        base.Print();
    }
}

int main() {
    Database db;
    // ifstream input("test.txt");
    string command;
    while (getline(cin, command)) {



        Instruction instruction;
        try {
            if (ParsingCommand(command, instruction, db)) {
                RunCommand(db, instruction);
            } else return 0;
        }
        catch (domain_error& except) {
            cout << except.what() << endl;
            return 0;
        }
    }
    return 0;
}