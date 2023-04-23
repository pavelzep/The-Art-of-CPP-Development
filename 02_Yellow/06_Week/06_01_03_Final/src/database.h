#pragma once 
#include "date.h"

#include <vector>
#include <functional>
#include <map>
#include <set>
#include <memory>

class Database {
public:
    void Add(const Date& date, const string& event);
    void Print(ostream& out);

    vector<pair<Date, shared_ptr<string>>> FindIf(function<bool(const Date&, const string&)> predicate);
    int RemoveIf(function<bool(const Date&, const string&)> predicate);
    string Last(const Date& date);

private:
    map<Date, Events> storage;
    map<Date, set<string>> store;
};


ostream& operator<<(ostream& out, const map<Date, set<string>>& store);
ostream& operator<<(ostream& out, const map<Date, Events>& store);


