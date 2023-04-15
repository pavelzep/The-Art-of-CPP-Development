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
    auto right_key = tie(left.year_, left.month_, left.day_);
    return left_key < right_key;
}

ostream& operator<<(ostream& out, const Date& date) {


    return out;
}

ostream& operator<<(ostream& out, const pair<Date&, string&>) {


    return out;
}