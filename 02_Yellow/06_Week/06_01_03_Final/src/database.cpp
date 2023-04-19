#include "database.h"



void Database::Add(const Date& date, const string& event) {
    store[date].insert(event);
}

void Database::Print(ostream& cout) {

}

vector<pair<Date&, string&>> Database::FindIf(function<bool(const Date&, const string&)> predicate) {
    return vector<pair<Date&, string&>>();
}

int Database::RemoveIf(function<bool(const Date& date, const string& str)> predicate) {
    for (auto& item : this->store) {
        for (auto& evt : item.)
    }
    return 0;
}

string Database::Last(const Date& date) {
    return string();
}

