#include <iostream>
#include <vector>
#include <string>
using namespace std;

void MoveStrings(vector<string> &source, vector<string> &destination) {
	for (int i = 0; i < (int)source.size(); ++i) {
		destination.push_back(source[i]);
	}
	source.clear();
}

int main() {

	vector<string> source = { "a", "b", "c" };
	vector<string> destination = { "z" };
	MoveStrings(source, destination);
	cout << source.size() << endl;

	for (const auto &str : destination) {
		cout << str << ' ';
	}

	return 0;
}
