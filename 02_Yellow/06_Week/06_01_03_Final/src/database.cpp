#include "database.h"

#include <algorithm>

void Database::Add(const Date& date, const string& event) {
    store[date].insert(event);

    if (storage[date].sortedEvents.insert(event).second) {
        storage[date].lastEvents.push_back(event);
    }

}

void Database::Print(ostream& out) {
    out << this->storage;
}

vector<pair<Date, shared_ptr<string>>> Database::FindIf(function<bool(const Date&, const string&)> predicate) {
    vector<pair<Date, shared_ptr<string>>> result;
    for (auto& item : this->store) {
        for (auto& evt : item.second) {
            if (predicate(item.first, evt)) {
                auto t = make_pair(item.first, make_shared<string>(evt));
                result.push_back(t);
            };
        }
    }
    return result;
}

int Database::RemoveIf(function<bool(const Date&, const string&)> predicate) {
    int count;
    for (auto& item : this->store) {
        for (auto it = item.second.begin();it != item.second.end();) {
            if (predicate(item.first, *it)) {
                it = item.second.erase(it);
                ++count;
            } else {
                ++it;
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

ostream& operator<<(ostream& out, const map<Date, Events>& store) {
    for (auto& item : store) {
        out << item.second;
    }
    return out;
}
