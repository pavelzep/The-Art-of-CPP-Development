#include "date.h"
#include <tuple>


Date ParseDate(istream& is) {
    int y, m, d;
    is >> y;
    is.ignore(1);
    is >> m;
    is.ignore(1);
    is >> d;
    return Date{ y,m,d };
}

bool operator<(const Date& left, const Date& right) {
    auto left_key = tie(left.year_, left.month_, left.day_);
    auto right_key = tie(right.year_, right.month_, right.day_);
    return left_key < right_key;
}

bool operator==(const Date& left, const Date& right) {
    return !(left < right) && !(right < left);
}

bool operator!=(const Date& left, const Date& right) {
    return !(left == right);
}

ostream& operator<<(ostream& out, const Date& date) {

    out << date.year_ << '-' << date.month_ << '-' << date.day_;
    return out;
}

ostream& operator<<(ostream& out, const pair < Date, set<string>>& record) {

    // out << record.first << ' ' << record.second;

    return out;
}