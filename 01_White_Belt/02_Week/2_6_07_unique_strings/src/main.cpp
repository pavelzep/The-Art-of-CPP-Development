#include <iostream>
#include <set>
#include <string>
using namespace std;

int main() {

	int stringCount;
	cin >> stringCount;
	set<string> uniqueStrings;

	while(stringCount){
		--stringCount;
		string str;
		cin>> str;
		uniqueStrings.insert(str);

	}
	cout << uniqueStrings.size() << endl;

	return 0;
}
