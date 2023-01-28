#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

map<char, int> BuildCharCounters(string word) {
	map<char, int> rezult;
	for (const auto &ch : word) {
		++rezult[ch];
	}
	return rezult;
}

void PrintMapCharInt(map<char, int> m) {
	for (const auto& [key, value] : m) {
		cout << key << ":" << value << " ";
	}
	cout << endl;
}

int main() {
	int q;
	cin >> q;

	vector<vector<string>> pairs;
	string a, b;

	while (q) {
		cin >> a >> b;
		vector<string> pair = { a, b };
		pairs.push_back(pair);
		--q;
	}
	for(const auto& pair: pairs){
		if( BuildCharCounters(pair[0])==BuildCharCounters(pair[1])) cout << "YES" << endl;
		else cout << "NO" << endl;
	}


	//PrintMapCharInt(BuildCharCounters("qwerty"));

	return 0;
}
