#include "phone_number.h"
#include <sstream>
#include <exception>


PhoneNumber::PhoneNumber(const string& international_number) {
    stringstream ss(international_number);
    if (ss.peek() != '+') {
        throw invalid_argument(international_number);
    }
    int country_code;
    ss.ignore(1);

    ss >> country_code;
    country_code_ = to_string(country_code);
    if (ss.peek() != '-') throw invalid_argument(international_number);
    ss.ignore(1);

    int city_code;
    ss >> city_code;
    city_code_ = to_string(city_code);

    if (ss.peek() != '-') throw invalid_argument(international_number);
    ss.ignore(1);

    ss >> this->local_number_;
}

string PhoneNumber::GetCountryCode() const {
    return country_code_;
}

string PhoneNumber::GetCityCode() const {
    return city_code_;
}

string PhoneNumber::GetLocalNumber() const {
    return local_number_;
}

string PhoneNumber::GetInternationalNumber() const {
    return "+" + country_code_ + "-" + city_code_ + "-" + local_number_; ;
}
