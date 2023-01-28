#include <iostream>
#include <cmath>

using namespace std;

int main() {
	double a,b,c;
	cin >> a>>b>>c;
	if(a){
		double d = b*b -4*a*c;
		if(d==0){
			cout << -(b/(2*a));
		}else{
			if(d>0){
				double s=sqrt(d);
				cout << (((-b)+s)/(2*a)) << ' ' << (((-b)-s)/(2*a)) ;
			}
		}
	 }else if(b) cout << -(c/b);
return 0;
}

