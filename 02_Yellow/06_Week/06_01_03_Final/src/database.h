#pragma once 
#include "date.h"




class Database {
public:
    void Add(const Date& date, const string& event);
    void Print(ostream& cout);

    string Last(Date& date);
};
