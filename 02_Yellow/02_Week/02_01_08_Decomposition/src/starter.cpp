#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>

using namespace std;
using store = map<string, vector<string>>;

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
    vector<string> stops;
};

istream& operator >> (istream& is, Query& q) {
    string operation_code;
    is >> operation_code;
    if (operation_code == "NEW_BUS") {
        q.type = QueryType::NewBus;
        is >> q.bus;
        int stop_count;
        is >> stop_count;
        //q.stops.clear();
        q.stops.resize(stop_count);
        for (string& stop : q.stops) {
            is >> stop;
            //q.stops.push_back(stop);
        }
    } else if (operation_code == "BUSES_FOR_STOP") {
        q.type = QueryType::BusesForStop;
        is >> q.stop;

    } else if (operation_code == "STOPS_FOR_BUS") {
        q.type = QueryType::StopsForBus;
        is >> q.bus;
    } else if (operation_code == "ALL_BUSES") {
        q.type = QueryType::AllBuses;
    }
    return is;
}

struct BusesForStopResponse {
    string stop;
    store busesForStop;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
    // Реализуйте эту функцию

    if (r.busesForStop.count(r.stop) == 0) {
        os << "No stop";
    } else {
        for (const string& bus : r.busesForStop.at(r.stop)) {
            cout << bus << " ";
        }
    }

    return os;
}

struct StopsForBusResponse {
    string bus;
    store stopsForBus;
    store busesForStop;
};

ostream& operator << (ostream& os, const StopsForBusResponse& r) {

    if (r.stopsForBus.count(r.bus) == 0) {
        os << "No bus";
    } else {
        for (const string& stop : r.stopsForBus.at(r.bus)) {
            os << "Stop " << stop << ": ";
            if (r.busesForStop.at(stop).size() == 1) {
                os << "no interchange";
            } else {
                for (const string& other_bus : r.busesForStop.at(stop)) {
                    if (r.bus != other_bus) {
                        os << other_bus << " ";
                    }
                }
            }
            if (stop != r.stopsForBus.at(r.bus).back()) os << endl;
        }
    }

    return os;
}

struct AllBusesResponse {
    store buses;
};

ostream& operator << (ostream& os, const AllBusesResponse& r) {

    if (r.buses.empty()) {
        cout << "No buses";
    } else {
        for (const auto& bus_item : r.buses) {
            cout << "Bus " << bus_item.first << ": ";
            for (const string& stop : bus_item.second) {
                cout << stop << " ";
            }
            cout << endl;
        }
    }

    return os;
}

class BusManager {
public:
    void AddBus(const string& bus, const vector<string>& stops) {
        buses_to_stops[bus] = stops;
        for (const auto& stop : stops) {
            stops_to_buses[stop].push_back(bus);
        }
    }

    BusesForStopResponse GetBusesForStop(const string& stop) const {
        BusesForStopResponse rez;
        rez.stop = stop;
        rez.busesForStop = this->stops_to_buses;
        return rez;
    }

    StopsForBusResponse GetStopsForBus(const string& bus) const {
        StopsForBusResponse rez;
        rez.bus = bus;
        rez.busesForStop = this->stops_to_buses;
        rez.stopsForBus = this->buses_to_stops;
        return rez;
    }

    AllBusesResponse GetAllBuses() const {
        AllBusesResponse rez;
        rez.buses = this->buses_to_stops;
        return rez;
    }

private:
    store buses_to_stops, stops_to_buses;
};



int main() {
    int query_count;
    Query q;

    cin >> query_count;

    BusManager bm;
    for (int i = 0; i < query_count; ++i) {
        cin >> q;
        switch (q.type) {
        case QueryType::NewBus:
            bm.AddBus(q.bus, q.stops);
            break;
        case QueryType::BusesForStop:

            cout << bm.GetBusesForStop(q.stop) << endl;
            break;
        case QueryType::StopsForBus:
            cout << bm.GetStopsForBus(q.bus) << endl;
            break;
        case QueryType::AllBuses:
            cout << bm.GetAllBuses() << endl;
            break;
        }
    }

    return 0;
}
