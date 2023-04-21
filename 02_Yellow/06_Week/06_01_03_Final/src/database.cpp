#include "database.h"



void Database::Add(const Date& date, const string& event) {
    store[date].insert(event);
}

void Database::Print(ostream& out) {
    out << this->store;
}

vector<pair<Date&, string&>> Database::FindIf(function<bool(const Date&, const string&)> predicate) {
    return vector<pair<Date&, string&>>();
}

int Database::RemoveIf(function<bool(const Date&, const string&)> predicate) {
    int count;
    for (auto& item : this->store) {
        for (auto& evt : item.second) {
            if (predicate(item.first, evt)) {
                ++count;
            };
        }
    }

    return count;
}

string Database::Last(const Date& date) {
    return string();
}


ostream& operator<<(ostream& out, const map<Date, set<string>>& store) {


    for (auto& item : store) {
        out << item;
    }

    return out;
}

