#pragma once 

#include <iostream>

using namespace std;

class Date {
public:
    // Date(const int year, const  int month, const  int day):year_(year), month_(month), day_(day) {
    // }
    const int year_ = 0;
    const int month_ = 0;
    const int day_ = 0;
private:


};

Date ParseDate(istream& is);

ostream& operator << (ostream& out, pair<Date&, string&>);