#include <iostream>
#include <vector>
using namespace std;

void printIntVect(vector<int> v) {
	//cout << "size: " << v.size() << endl;

	for (const auto &val : v) {
		cout << val << ' ';
	}
	cout << endl;
}

int calcAverageTemp(const vector<int> &temp) {
	int rez = 0;
	for (const auto &val : temp) {
		rez += val;
	}
	rez /= temp.size();
	return rez;
}

vector<int> HighTempDayNumbers(const vector<int> &temp) {
	vector<int> highTempDayNumbers;
	int avrTemp = calcAverageTemp(temp);

	for (int i = 0; i < temp.size(); ++i) {
		if (temp[i] > avrTemp) {
			highTempDayNumbers.push_back(i);
		}
	}

	return highTempDayNumbers;
}

int main() {

	int number;
	cin >> number;
	vector<int> temperature(number);

	for (auto &t : temperature) {
		cin >> t;
	}

	//vector<int> temperature = { 1, 2, 3, 4, 5, 6 };
	//printVect(temperature);
	//cout << "avr temp: " << calcAverageTemp(temperature) << endl;

	vector<int> highTempDayNumbers = HighTempDayNumbers(temperature);

	cout << highTempDayNumbers.size() << endl;
	printIntVect(highTempDayNumbers);

	return 0;
}
