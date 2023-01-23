#include <fstream>

using namespace std;

int main() {
	ifstream input("input.txt");
	ofstream output("output.txt");

	string line;
	if (input) {
		while (getline(input, line)) {
			output << line << endl;
		}
	}

	return 0;
}
