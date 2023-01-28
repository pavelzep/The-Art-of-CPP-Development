#include <iostream>
#include <string>
using namespace std;

int main() {
	int pos = -2;
	int count = 0;
	string str;
	cin >> str;

	for(int i=0; i<(int)str.size();i++){
		if(str[i]=='f'){
			pos=-1;
			if(count == 1) {
				pos=i;
				break;
			}
			count++;
		}
	}




	cout << pos;
	return 0;
}
