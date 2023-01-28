#include <iostream>
#include <algorithm>
using namespace std;

int main() {

	int a,b;
	cin>> a >> b;
/*
	gcd=1;
	//if (max(a,b)%min(a,b)==0) cout << min(a,b);

	for(int i=1; i<=min(a,b); i++){
		if(a%i==0 && b%i==0) gcd=i;
	}
*/	if(a==b){
		cout << a;
	}else{
		if(max(a,b)%min(a,b)==0) cout << min(a,b);
		else{
			while (a>0 && b>0){
				if(a>b) a=a%b;
				else b=b%a;
			}
			cout <<a+b;
		}
	}
	return 0;
}
