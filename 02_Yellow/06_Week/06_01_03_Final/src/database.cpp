#include "database.h"




void Database::Add(const Date& date, const string& event) {
    store[date].insert(event);
}

void Database::Print(ostream& out) {
    out << this->store;
}

vector<pair<Date, string>> Database::FindIf(function<bool(const Date&, const string&)> predicate) {

    vector<pair<Date, string>> result;
    //int count;
    for (auto& item : this->store) {
        for (auto& evt : item.second) {
            if (predicate(item.first, evt)) {
                //item.second.erase(evt);
                auto& r_Date = item.first;
                auto& r_evt = evt;
                auto t = make_pair(r_Date, r_evt);
                result.push_back(t);
                //++count;
            };
        }
        //return count;
    }

    return result;
}

int Database::RemoveIf(function<bool(const Date&, const string&)> predicate) {
    int count;
    for (auto& item : this->store) {
        bool flag = 0;
        for (auto& evt : item.second) {
            if (predicate(item.first, evt)) {
                // item.second.erase(evt);
                flag = 1;
                ++count;
            };
            if (flag) {
                item.second.erase(evt);
                flag = 0;
            }
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

