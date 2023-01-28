#include <iostream>
#include <map>
#include <set>
#include <string>

using namespace std;
void print(map<string, set<string>> _map) {
	for (const auto &item : _map) {
		cout << item.first << ": ";
		for (const auto &_item : item.second) {
			cout << _item;
		}
		cout << endl;
	}
}

void print2(set<string> &_set) {
	for (const auto &_item : _set) {
		cout << _item;
	}
	cout << endl;
}

int main() {

	int taskCount;
	cin >> taskCount;

	map<string, set<string>> synonyms;

	while (taskCount) {
		--taskCount;

		string task;
		cin >> task;
		if (task == "ADD") {
			string str1, str2;
			cin >> str1 >> str2;

			synonyms[str1].insert(str2);
			synonyms[str2].insert(str1);


		} else if (task == "COUNT") {

			string str;
			cin >> str;
			cout << synonyms[str].size() << endl;

		} else if (task == "CHECK") {
			string str1, str2;
			cin >> str1 >> str2;

			if (synonyms.count(str1) && synonyms[str1].count(str2)) {
				cout << "YES" << endl;
			} else {
				cout << "NO" << endl;
			}

		}

	}

	return 0;
}
