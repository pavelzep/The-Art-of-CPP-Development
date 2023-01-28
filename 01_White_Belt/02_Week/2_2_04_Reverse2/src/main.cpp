#include <iostream>
#include <vector>

using namespace std;

vector<int> Reversed(const vector<int> &v) {

	vector<int> rez;
	for (int i = (int)v.size() - 1; i >= 0; --i) {
		rez.push_back(v[i]);
	}
	return rez;

}

int main() {

	vector<int> numbers = { 1, 5, 3, 4, 2 };

	for (const auto &a : Reversed(numbers))
		cout << a << ' ';
	return 0;
}
