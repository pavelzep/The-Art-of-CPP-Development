#include "airline_ticket.h"
#include "test_runner.h"

#include <algorithm>
#include <numeric>
#include <tuple>
#include <iomanip>

using namespace std;


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

#define SORT_BY(x)                                                        \
   [](const AirlineTicket& lhs, const AirlineTicket& rhs) {               \
    return lhs.x < rhs.x;                                                 \
  }                                                                         

void TestSortBy() {
    vector<AirlineTicket> tixs = {
      {"VKO", "AER", "Utair",     {2018, 2, 28}, {17, 40}, {2018, 2, 28}, {20,  0}, 1200},
      {"AER", "VKO", "Utair",     {2018, 3,  5}, {14, 15}, {2018, 3,  5}, {16, 30}, 1700},
      {"AER", "SVO", "Aeroflot",  {2018, 3,  5}, {18, 30}, {2018, 3,  5}, {20, 30}, 2300},
      {"PMI", "DME", "Iberia",    {2018, 2,  8}, {23, 00}, {2018, 2,  9}, { 3, 30}, 9000},
      {"CDG", "SVO", "AirFrance", {2018, 3,  1}, {13, 00}, {2018, 3,  1}, {17, 30}, 8000},
    };

    sort(begin(tixs), end(tixs), SORT_BY(price));
    ASSERT_EQUAL(tixs.front().price, 1200);
    ASSERT_EQUAL(tixs.back().price, 9000);

    sort(begin(tixs), end(tixs), SORT_BY(from));
    ASSERT_EQUAL(tixs.front().from, "AER");
    ASSERT_EQUAL(tixs.back().from, "VKO");

    sort(begin(tixs), end(tixs), SORT_BY(arrival_date));
    ASSERT_EQUAL(tixs.front().arrival_date, (Date{ 2018, 2, 9 }));
    ASSERT_EQUAL(tixs.back().arrival_date, (Date{ 2018, 3, 5 }));
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestSortBy);
}
