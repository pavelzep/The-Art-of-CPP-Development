#include <iostream>
#include <string>
#include <vector>
using namespace std;

bool IsPalindrom(string a) {
	int strSize = a.size();
	for (int i = 0; i < strSize / 2; ++i) {
		if (a[i] != a[strSize - 1 - i]) {
			return false;
		}
	}
	return true;
}

vector<string> PalindromFilter(vector<string> words, int minLength) {
	vector<string> pf;
	for (auto str : words) {
		if ((int)str.size() >= minLength) {
			if (IsPalindrom(str)) {
				pf.push_back(str);
			}
		}
	}
	return pf;
}

int main() {
	vector<string> rez;
	vector<string> w1 = { "abacaba", "aba" };
	vector<string> w2 = { "abafcfaba", "fabaf", "faggbggaf" };
	vector<string> w3 = { "weew", "bro", "code", "abacaba", "aba" };

	rez = PalindromFilter(w3, 4);
	for (const auto &str : rez) {
		cout << str << ' ' << endl;
	}

	return 0;
}
