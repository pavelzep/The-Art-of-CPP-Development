#include "phone_number.h"

#include <vector>
#include <iostream>


ostream& operator << (ostream& os, const PhoneNumber& p) {

    os << p.GetInternationalNumber() << std::endl;
    os << '+' << p.GetCountryCode() << '-' << p.GetCityCode() << '-' << p.GetLocalNumber();
    return os;
};

int main() {

    vector<string> numbers = { "+7-495-111-22-33","+7-495-1112233","+323-22-460002","+1-2-coursera-cpp" , "+7-1233" };

    for (size_t i = 0; i < numbers.size(); i++) {
        PhoneNumber phone(numbers.at(i));
        std::cout << phone << std::endl;
    }
    return 0;
}