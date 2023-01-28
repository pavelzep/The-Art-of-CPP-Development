#include <iostream>
#include <vector>
#include <map>
#include <string>
using namespace std;
int main() {
	map<vector<string> ,int > busMap;
	int reqestCount;
	cin >> reqestCount;
	while (reqestCount) {
		--reqestCount;
		int stopCount;
		cin >> stopCount;
		vector<string> stopNames(stopCount);
		for (auto &stopName : stopNames) {
			cin >> stopName;
		}
		if(busMap.count(stopNames)==0){
			int mapSize = busMap.size();
			busMap[stopNames]=mapSize;
			cout << "New bus " << mapSize+1<< endl;
		}else{
			cout << "Already exists for " << busMap[stopNames]+1  << endl;
		}
	}
	return 0;
}
