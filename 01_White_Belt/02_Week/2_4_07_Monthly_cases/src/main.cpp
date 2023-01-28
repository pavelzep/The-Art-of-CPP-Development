#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
	int currentMonth = 0;

	const vector<int> daysInMonth = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31,
			30, 31 };

	vector<vector<string> > monthlyCases(daysInMonth[currentMonth]);

	int q;
	cin >> q;
	for (int j = 0; j < q; ++j) {
		string operation_code;
		cin >> operation_code;
		if (operation_code == "ADD") {
			int i = 0;
			cin >> i;
			string s;
			cin >> s;
			monthlyCases[i - 1].push_back(s);
		} else if (operation_code == "DUMP") {
			int i = 0;
			cin >> i;
			cout << monthlyCases[i - 1].size();
			for (const auto &val : monthlyCases[i - 1]) {
				cout << ' ' << val;
			}
			cout << endl;
		} else if (operation_code == "NEXT") {
			int nextMonth;
			if (currentMonth == 11)
				nextMonth = 0;
			else
				nextMonth = currentMonth + 1;

			int daysInCurrentMonth = daysInMonth[currentMonth];
			int daysInNextMonth = daysInMonth[nextMonth];

			if (daysInNextMonth < daysInCurrentMonth) {
				for (int i = daysInNextMonth; i < daysInCurrentMonth; ++i) {
					monthlyCases[daysInNextMonth - 1].insert(
							end(monthlyCases[daysInNextMonth - 1]),
							begin(monthlyCases[i]), end(monthlyCases[i]));
				}
			}
			currentMonth = nextMonth;
			monthlyCases.resize(daysInNextMonth);
			//cout << "!!!!! next: " << monthlyCases.size() << endl;
		}
	}
	return 0;
}
