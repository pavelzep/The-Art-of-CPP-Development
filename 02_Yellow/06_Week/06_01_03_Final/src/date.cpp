#include "date.h"

Date ParseDate(istream& is) {
    int y, m, d;
    is >> y;
    is.ignore(1);
    is >> m;
    is.ignore(1);
    is >> d;
    return Date{ y,m,d };
}

ostream& operator<<(ostream& out, const Date& date) {


    return out;
}

ostream& operator<<(ostream& out, const pair<Date&, string&>) {


    return out;
}