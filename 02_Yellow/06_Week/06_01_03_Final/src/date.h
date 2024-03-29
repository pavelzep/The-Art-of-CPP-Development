#pragma once 

#include <iostream>
#include <set>
#include <memory>
#include "events.h"

using namespace std;

class Date {
public:
    Date(const int year, const  int month, const  int day):year_(year), month_(month), day_(day) {
    }
    const int year_ = 0;
    const int month_ = 0;
    const int day_ = 0;
};

Date ParseDate(istream& is);

bool operator<(const Date& left, const Date& right);
bool operator==(const Date& left, const Date& right);
bool operator!=(const Date& left, const Date& right);

ostream& operator << (ostream& out, const Date& date);
ostream& operator << (ostream& out, const pair < Date, string>& record);
// ostream& operator << (ostream& out, const pair < Date, shared_ptr<string>>& record);
ostream& operator << (ostream& out, const pair < Date, Events>& record);