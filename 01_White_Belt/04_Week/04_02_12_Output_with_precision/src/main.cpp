#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

using namespace std;

int main() {
	ifstream input("input.txt");

	string line;
	if (input) {
		while (getline(input, line)) {
			cout << fixed << setprecision(3) << stod(line)<< endl;
		}
	}
	return 0;
}
