#include "database.h"



void Database::Add(const Date& date, const string& event) {
    store[date].insert(event);
}

void Database::Print(ostream& cout) {
}

