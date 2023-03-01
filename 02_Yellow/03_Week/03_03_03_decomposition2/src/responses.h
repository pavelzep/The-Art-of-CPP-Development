#pragma once

#include <string>
#include <map>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

using store = map<string, vector<string>>;

struct BusesForStopResponse {
    string stop;
    store busesForStop;
};



struct StopsForBusResponse {
    string bus;
    store stopsForBus;
    store busesForStop;
};

struct AllBusesResponse {
    store buses;
};

ostream& operator << (ostream& os, const StopsForBusResponse& r);

ostream& operator << (ostream& os, const BusesForStopResponse& r);

ostream& operator << (ostream& os, const AllBusesResponse& r);