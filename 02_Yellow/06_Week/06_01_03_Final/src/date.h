#pragma once 

#include <iostream>

using namespace std;

class Date {
public:
    Date(const int year, const  int month, const  int day):year_(year), month_(month), day_(day) {
    }

    Date():year_(0), month_(0), day_(0) {

    }

    int GetYear() const {
        return year_;
    }
    int GetMonth() const {
        return month_;
    }
    int GetDay() const {
        return day_;
    }

private:
    const int year_ = 0;
    const int month_ = 0;
    const int day_ = 0;
};

Date ParseDate(istream& is);

ostream& operator<<(ostream& out, const Date& date);

ostream& operator << (ostream& out, pair<Date&, string&>);