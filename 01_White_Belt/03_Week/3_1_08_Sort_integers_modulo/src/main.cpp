#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

void print(vector<int> v){
	for(const auto& i:v){
		cout << i<< ' ';
	}
	cout << endl;
}


int main() {
	int count;

	cin >> count;
	vector<int> numbers;
	while (count) {
		--count;
		int n;
		cin >> n;
		numbers.push_back(n);
	}
	sort(begin(numbers), end(numbers), [](int x, int y) {	return abs(x)<abs(y);});

	print(numbers);


	return 0;
}
