#pragma once 
#include "date.h"

#include <vector>
#include <functional>
#include <map>
#include <set>


class Database {
public:
    void Add(const Date& date, const string& event);
    void Print(ostream& cout);

    vector<pair<Date&, string&>> FindIf(function<bool(const Date&, const string&)> predicate);
    int RemoveIf(function<bool(const Date&, const string&)> predicate);
    string Last(const Date& date);

private:
    map<Date, set<string>> store;


};


