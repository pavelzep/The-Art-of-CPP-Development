#include <iostream>
#include <map>
#include <set>
#include <string>

using namespace std;

int main() {
	map<set<string>, int> busMap;
	int reqestCount;
	cin >> reqestCount;

	while (reqestCount) {
		--reqestCount;

		int stopCount;
		cin >> stopCount;

		set<string> bus;

		while (stopCount) {
			--stopCount;
			string stop;
			cin >> stop;

			bus.insert(stop);
		}
		if (busMap.count(bus)==0) {

			int busNumber = busMap.size() + 1;
			busMap[bus] = busNumber;

			cout << "New bus " << busNumber << endl;
		} else {
			cout << "Already exists for " << busMap[bus] << endl;
		}
	}
	return 0;
}
