
#include <iostream>
using namespace std;

int main() {
	double n, a, b, x, y, c;

	cin >> n >> a >> b >> x >> y ;

	if( n>0 && a>0 && b>0 && x>0 && y>0 && x<=100 && y<=100 && a<b){
		if(n<=a)c=n;
		else{
			if(n>b) c=n*(1-(y/100));
			else c=n*(1-(x/100));
		}
		cout << c << endl;
	}
	return 0;
}
