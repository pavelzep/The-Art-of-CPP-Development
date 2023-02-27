#include "phone_number.h"
#include <sstream>
#include <exception>

PhoneNumber::PhoneNumber(const string& international_number) {
    stringstream ss(international_number);
    if (ss.peek() != '+') {
        throw invalid_argument(international_number);
    }
    ss.ignore(1);
    ss >> this->country_code_;
    if (ss.peek() != '-') {
        throw invalid_argument(international_number);
    }
    ss.ignore(1);
    ss >> this->city_code_;
    if (ss.peek() != '-') {
        throw invalid_argument(international_number);
    }
    ss.ignore(1);
    ss >> this->local_number_;
}

string PhoneNumber::GetCountryCode() const {
    return string();
}

string PhoneNumber::GetCityCode() const {
    return string();
}

string PhoneNumber::GetLocalNumber() const {
    return string();
}

string PhoneNumber::GetInternationalNumber() const {
    return string();
}
