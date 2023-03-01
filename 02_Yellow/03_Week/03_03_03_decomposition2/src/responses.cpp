#include "responses.h"

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
    if (r.busesForStop.count(r.stop) == 0) {
        os << "No stop";
    } else {
        for (const string& bus : r.busesForStop.at(r.stop)) {
            cout << bus << " ";
        }
    }

    return os;
}

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