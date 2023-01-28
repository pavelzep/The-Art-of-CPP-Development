#include <string>
#include <map>
#include <vector>
#include <iostream>
using namespace std;

bool IsKey(map<string, string> _map, string _key) {
	for (const auto &item : _map) {
		if (item.first == _key)
			return 1;
	}
	return 0;
}
bool IsValue(map<string, string> _map, string _value) {
	for (const auto &item : _map) {
		if (item.second == _value)
			return 1;
	}
	return 0;
}

int main() {
	int q;
	cin >> q;
	map<string, string> capitals;

	while (q) {

		string task;
		cin >> task;

		if (task == "CHANGE_CAPITAL") {
			string country, capital;
			cin >> country >> capital;

			if (IsKey(capitals, country)) { //если такая страна есть
				if (IsValue(capitals, capital)) { //если такая столица есть
					cout << "Country " << country
							<< " hasn't changed its capital " << endl;
				} else { //если такой столицы нет
					cout << "Country " << country
							<< " has changed its capital from "
							<< capitals[country] << " to " << capital << endl;
				}
			} else { //если такой страны нет
				cout << "Introduce new country " << country << " with capital "
						<< capital << endl;

			}

			capitals[country] = capital;

		} else if (task == "RENAME") {
			string old_country_name, new_country_name;
			cin >> old_country_name >> new_country_name;
			if (old_country_name == new_country_name
					|| !IsKey(capitals, old_country_name)
					|| IsKey(capitals, new_country_name)) {
				cout << "Incorrect rename, skip" << endl;
			} else {
				string capital = capitals[old_country_name];
				cout << "Country " << old_country_name << " with capital "
						<< capital << " has been renamed to "
						<< new_country_name << endl;

				capitals.erase(old_country_name);
				capitals[new_country_name] = capital;

			}

		} else if (task == "ABOUT") {
			string country;
			cin >> country;
			if (IsKey(capitals, country)) {
				cout << "Country " << country << " has capital "
						<< capitals[country] << endl;
			} else {
				cout << "Country " << country << " doesn't exist" << endl;
			}

		} else if (task == "DUMP") {

			if (capitals.size() != 0) {
				for (const auto &item : capitals) {
					cout << item.first << '/' << item.second << " ";
				}
				cout << endl;
			} else {
				cout << "There are no countries in the world" << endl;
			}
		}

		--q;
	}
	return 0;
}
