#include <iostream>
#include <vector>
#include <cctype>
#include <algorithm>
using namespace std;

string toLowerStr(string &str) {
	string rezult;
	for (auto &c : str) {
		rezult.push_back(tolower(c));
	}
	return rezult;
}

void sortVect(vector<string> &vect) {
	sort(vect.begin(), vect.end(), [](string str1, string str2) {
		return (toLowerStr(str1) < toLowerStr(str2));
	});
}

int main() {

	int stringCount;
	cin >> stringCount;
	vector<string> stringVect(stringCount);
	for (auto &str : stringVect) {
		cin >> str;
	}
	sortVect(stringVect);
	for (const auto &str : stringVect) {
		cout << str << ' ';
	}
	return 0;
}
