#include "date.h"
#include <tuple>
#include <iomanip>


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
    out << setw(4) << setfill('0') << date.year_ << '-' << setw(2) << setfill('0') << date.month_ << '-' << setw(2) << setfill('0') << date.day_;
    return out;
}

ostream& operator << (ostream& out, const pair < Date, string>& record) {
    out << record.first << ' ' << record.second;
    return out;
}

ostream& operator<<(ostream& out, const pair < Date, set<string>>& record) {
    for (const auto& item : record.second) {
        out << record.first << ' ' << item << endl;
    }
    return out;
}