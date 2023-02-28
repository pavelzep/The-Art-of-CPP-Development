#include "bus_manager.h"


void BusManager::AddBus(const string& bus, const vector<string>& stops) {
    buses_to_stops[bus] = stops;
    for (const auto& stop : stops) {
        stops_to_buses[stop].push_back(bus);
    }
}

BusesForStopResponse BusManager::GetBusesForStop(const string& stop) const {
    BusesForStopResponse rez;
    rez.stop = stop;
    rez.busesForStop = this->stops_to_buses;
    return rez;
}

StopsForBusResponse BusManager::GetStopsForBus(const string& bus) const {
    StopsForBusResponse rez;
    rez.bus = bus;
    rez.busesForStop = this->stops_to_buses;
    rez.stopsForBus = this->buses_to_stops;
    return rez;
}

AllBusesResponse BusManager::GetAllBuses() const {
    AllBusesResponse rez;
    rez.buses = this->buses_to_stops;
    return rez;
}