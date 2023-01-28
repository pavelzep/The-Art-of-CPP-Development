#include <iostream>
using namespace std;

int main() {

	int a,b;
	cin >> a >> b;


	if(!( 1<=a && a<=b && b<=30000 )) return 0;
	while(a <=b){
		if(a%2==0){
			cout << a << ' ';
		}
		++a;
	}
	return 0;
}
