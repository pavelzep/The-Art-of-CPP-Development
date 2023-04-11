#pragma once 
#include "date.h"

#include <vector>



class Database {
public:
    void Add(const Date& date, const string& event);
    void Print(ostream& cout);

    vector<pair<Date&, string&>&> FindIf();
    int RemoveIf();

    string Last(Date& date);
};
