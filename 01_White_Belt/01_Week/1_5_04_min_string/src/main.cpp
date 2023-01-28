#include <iostream>
#include <string>
using namespace std;

int main() {
	string a,b,c,min;
	cin >> a >> b >> c;
	if(a<b){
		if(a<c)	min=a;
		else min=c;
		}
	else{
		if(b<c)min=b;
		else min=c;
	}
	cout << min ;
	return 0;
}
