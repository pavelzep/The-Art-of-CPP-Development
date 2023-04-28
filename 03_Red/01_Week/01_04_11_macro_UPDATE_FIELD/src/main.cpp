#include "airline_ticket.h"
#include "test_runner.h"

#include <sstream>
#include <iomanip>

using namespace std;

istream& operator>>(istream& is, Date& date) {

    is >> date.year;
    is.ignore(1);
    is >> date.month;
    is.ignore(1);
    is >> date.day;

    return is;
}

istream& operator>>(istream& is, Time& time) {
    is >> time.hours;
    is.ignore(1);
    is >> time.minutes;
    return is;
}

bool operator<(const Date& left, const Date& right) {
    auto left_key = tie(left.year, left.month, left.day);
    auto right_key = tie(right.year, right.month, right.day);
    return left_key < right_key;
}

bool operator==(const Date& left, const Date& right) {
    return !(left < right) && !(right < left);
}

bool operator<(const Time& left, const Time& right) {
    auto left_key = tie(left.hours, left.minutes);
    auto right_key = tie(right.hours, right.minutes);
    return left_key < right_key;
}

bool operator==(const Time& left, const Time& right) {
    return !(left < right) && !(right < left);
}

ostream& operator<<(ostream& out, const Date& date) {
    out << setw(4) << setfill('0') << date.year << '-' << setw(2) << setfill('0') << date.month << '-' << setw(2) << setfill('0') << date.day;
    return out;
}
ostream& operator<<(ostream& out, const Time& time) {
    out << setw(2) << setfill('0') << time.hours << ':' << setw(2) << setfill('0') << time.minutes;
    return out;
}

// Реализуйте этот макрос, а также необходимые операторы для классов Date и Time
#define UPDATE_FIELD(ticket, field, values) {\
  map<string, string>::const_iterator it;\
  it = values.find(#field);\
  if (it != values.end()) {\
    istringstream in(it->second);\
    in >> ticket.field;\
  }\
}





void TestUpdate() {
    AirlineTicket t;
    t.price = 0;

    const map<string, string> updates1 = {
      {"departure_date", "2018-2-28"},
      {"departure_time", "17:40"},
    };
    UPDATE_FIELD(t, departure_date, updates1);
    UPDATE_FIELD(t, departure_time, updates1);
    UPDATE_FIELD(t, price, updates1);

    ASSERT_EQUAL(t.departure_date, (Date{ 2018, 2, 28 }));
    ASSERT_EQUAL(t.departure_time, (Time{ 17, 40 }));
    ASSERT_EQUAL(t.price, 0);

    const map<string, string> updates2 = {
      {"price", "12550"},
      {"arrival_time", "20:33"},
    };
    UPDATE_FIELD(t, departure_date, updates2);
    UPDATE_FIELD(t, departure_time, updates2);
    UPDATE_FIELD(t, arrival_time, updates2);
    UPDATE_FIELD(t, price, updates2);

    // updates2 не содержит ключей "departure_date" и "departure_time", поэтому
    // значения этих полей не должны измениться
    ASSERT_EQUAL(t.departure_date, (Date{ 2018, 2, 28 }));
    ASSERT_EQUAL(t.departure_time, (Time{ 17, 40 }));
    ASSERT_EQUAL(t.price, 12550);
    ASSERT_EQUAL(t.arrival_time, (Time{ 20, 33 }));
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestUpdate);
}
