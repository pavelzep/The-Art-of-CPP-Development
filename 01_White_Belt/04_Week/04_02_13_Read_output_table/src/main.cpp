#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

int main() {
	ifstream input("input.txt");

	int columns;
	int rows;

	vector<vector<int>> data;
	if (input) {
		input >> rows >> columns;
		for (int j = 0; j < rows; ++j) {
			vector<int> temp;
			int val;
			for (int i = 0; i < columns; ++i) {
				input >> val;
				input.ignore(1);
				temp.push_back(val);
			}
			data.push_back(temp);
		}
	}

	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < columns; ++j) {

			cout << right << setw(10);
			cout << data.at(i).at(j);
			if (j < columns - 1)
				cout << ' ';
		}
		if (i < rows)
			cout << endl;
	}
	return 0;
}
