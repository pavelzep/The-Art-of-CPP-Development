#include <string>
#include <map>
#include <vector>
#include <iostream>
using namespace std;

bool isVectIncludeString(const vector<string> &_storage, const string &_item) {
	for (const auto &item : _storage) {
		if (item == _item)
			return 1;
	}
	return 0;
}

bool isKey(map<string, vector<string>> _map, string _key) {
	for (const auto &item : _map) {
		if (item.first == _key)
			return 1;
	}
	return 0;
}

/*bool isValue(map<string, vector<string>> _map, string _value) {
 for (const auto &item : _map) {
 if (item.second == _value)
 return 1;
 }
 return 0;
 }*/

int main() {
	int requestCount;
	cin >> requestCount;

	map<string, vector<string>> busesStopsMap;
	map<string, vector<string>> busesNamesMap;

	while (requestCount) {
		--requestCount;

		string request;
		cin >> request;

		if (request == "NEW_BUS") {
			string busName;
			int stopCount;
			cin >> busName >> stopCount;

			vector<string> busStops;
			while (stopCount) {
				--stopCount;
				string stopName;
				cin >> stopName;
				busStops.push_back(stopName);
				busesNamesMap[stopName].push_back(busName);
			}
			busesStopsMap[busName] = busStops;

		} else if (request == "BUSES_FOR_STOP") {
			string stopName;
			cin >> stopName;
			if (isKey(busesNamesMap, stopName)) {
				for (const auto &item : busesNamesMap[stopName]) {
					cout << item << ' ';
				}
				cout << endl;
			} else {
				cout << "No stop" << endl;
			}

		} else if (request == "STOPS_FOR_BUS") {
			string busName;
			cin >> busName;
			if (isKey(busesStopsMap, busName)) {
				for (const auto &stopName : busesStopsMap[busName]) {

					cout << "Stop " << stopName << ": ";

					for (const auto &_busName : busesNamesMap[stopName]) {
						if (busesNamesMap[stopName].size()>1) {
							if (_busName != busName) {
								cout << _busName << ' ';
							}
						}else{
							cout << "no interchange";
						}
					}
					cout << endl;
				}

			} else {
				cout << "No bus" << endl;
			}

		} else if (request == "ALL_BUSES") {

			if(busesStopsMap.size()<1){
				cout << "No buses" << endl;
			}else{
				for (const auto &item: busesStopsMap ){
					cout << "Bus " << item.first << ": ";
					for(const auto &_item: item.second){
						cout << _item << " ";
					}
					cout << endl;
				}


			}

		}

	}
	return 0;
}
