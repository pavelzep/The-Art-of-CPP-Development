#pragma once

#include <vector>
#include <string> 
#include <iostream>

using namespace std;

enum class QueryType {
    NewBus,
    BusesForStop,
    StopsForBus,
    AllBuses
};

struct Query {
    QueryType type;
    string bus;
    string stop;
    vector <string> stops;
};

istream& operator >> (istream& is, Query& q);