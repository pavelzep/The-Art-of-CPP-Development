#pragma once

#include <string>
#include <map>
#include <string>
#include <vector>

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

ostream& operator << (ostream& os, const StopsForBusResponse& r);

ostream& operator << (ostream& os, const AllBusesResponse& r);

