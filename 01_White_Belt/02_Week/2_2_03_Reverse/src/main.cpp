#include <iostream>
#include <vector>

using namespace std;

void Reverse(vector<int> &v) {
	int temp;
	for (int i = 0; i < (int)v.size() / 2; ++i) {
		temp = v[i];
		v[i] = v[v.size() - 1 - i];
		v[v.size() - 1 - i] = temp;
	}
}

int main() {

	vector<int> numbers = { 1, 5, 3, 4, 2 };
	Reverse(numbers);
	for (const auto &a : numbers)
		cout << a << ' ';
	return 0;
}
