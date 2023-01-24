#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

int main() {
	ifstream input("input.txt");
	ofstream output("output.txt");

	int columns;
	int rows;
		
	vector<vector<int>> data;
	if (input) {
		input >> rows >> columns;
		for(int j=0; j< rows ; ++j){
			vector<int> temp;
			int val;
			for(int i =0; i< columns ;++i){
			input >> val;
			input.ignore(1);
			temp.push_back(val);
			}
			data.push_back(temp);
	
		}	
	}
	
	cout << rows << ' ' << columns << endl;
	
	for( const auto & row: data){
		for(const auto & column: row ){
			cout << right;
			cout << setw(11);
			cout << column ;
		}
		cout << endl;
	}
	return 0;
}
