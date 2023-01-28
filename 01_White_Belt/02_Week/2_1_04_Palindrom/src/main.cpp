#include <iostream>
#include <string>
using namespace std;

bool IsPalindrom(string a) {
	bool flag = 1;
	int strSize = a.size();
	for (int i = 0; i < strSize / 2; ++i) {
		if (a[i] != a[strSize - 1 - i]) {
			flag = 0;
			break;
		}
	}
	return flag;
}

int main() {
	string str;
	cin >> str;

	cout << IsPalindrom(str);
	return 0;
}
