#include "database.h"

#include <algorithm>
#include <sstream>

void Database::Add(const Date& date, const string& event) {
    if (storage[date].sortedEvents.insert(event).second) {
        storage[date].lastEvents.push_back(event);
    }

}

void Database::Print(ostream& out) const {
    out << this->storage;
}

vector<pair<Date, shared_ptr<string>>> Database::FindIf(function<bool(const Date&, const string&)> predicate) const {
    vector<pair<Date, shared_ptr<string>>> result;
    for (auto& item : this->storage) {
        for (auto& evt : item.second.lastEvents) {
            if (predicate(item.first, evt)) {
                auto t = make_pair(item.first, make_shared<string>(evt));
                result.push_back(t);
            };
        }
    }
    return result;
}

int Database::RemoveIf(function<bool(const Date&, const string&)> predicate) {
    int count = 0;

    for (auto it_map = storage.begin(); it_map != storage.end();) {
        for (auto it = it_map->second.sortedEvents.begin();it != it_map->second.sortedEvents.end();) {
            if (predicate(it_map->first, *it)) {
                it = it_map->second.sortedEvents.erase(it);
                ++count;
            } else {
                ++it;
            }
        }
        auto it = stable_partition(it_map->second.lastEvents.begin(), it_map->second.lastEvents.end(), [&](string evt) {return !predicate(it_map->first, evt);});
        it_map->second.lastEvents.erase(it, it_map->second.lastEvents.end());

        if (it_map->second.sortedEvents.size() == 0) {
            it_map = storage.erase(it_map);
        } else {
            ++it_map;
        }
    }

    return count;
}

string Database::Last(const Date& date) const {
    stringstream ss;
    auto date_pair = make_pair(date, Events{});
    auto func = [](const pair<Date, Events>& left, const pair<Date, Events>& right) {
        return left.first < right.first;
    };
    if (date < storage.begin()->first) ss << "No entries";
    else if (storage.size() == 0) ss << "No entries";
    else {

        auto it = --upper_bound(storage.begin(), storage.end(), date_pair, func);
        ss << it->first << ' ' << it->second.lastEvents.back();
    }

    return  ss.str();
}

ostream& operator<<(ostream& out, const map<Date, Events>& store) {
    for (auto& item : store) {
        out << item;
    }
    return out;
}
