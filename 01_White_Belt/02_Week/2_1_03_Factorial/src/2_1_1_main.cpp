#include <iostream>
using namespace std;

int Factorial(int n) {
	int f = 1;
	if (n < 0)
		return f;
	for (int i = 1; i <= n; ++i) {
		f *= i;
	}
	return f;
}

int main() {
	int n;
	cin >> n;
	cout << Factorial(n);
	return 0;
}

