#include <iostream>
#include <vector>
#include <string>

using namespace std;

void CommandHandler(vector<bool> &queue, const vector<string> &commands,
		const vector<int> &params, int i) {
	string command = commands[i];
	int param = params[i];
	if (command == "WORRY") {
		queue[param] = 1;
	} else if (command == "QUIET") {
		queue[param] = 0;
	} else if (command == "COME") {
		if (param > 0) {
			for (int i = 0; i < param; ++i) {
				queue.push_back(0);
			}
		} else if (param < 0) {
			for (int i = 0; i < -(param); ++i) {
				queue.pop_back();
			}
		}
	}

	else if (command == "WORRY_COUNT") {
		int worryCount = 0;
		for (const auto &val : queue) {
			if (val == 1)
				++worryCount;
		}
		cout << worryCount << endl;
	}
}

int main() {

	int numberOfCommands = 0;
	cin >> numberOfCommands;

	vector<string> commands;
	vector<int> params;
	vector<bool> queue;
	{
		int n = numberOfCommands;
		while (n > 0) {
			string s;
			int par = 0;
			cin >> s;
			commands.push_back(s);
			if (s != "WORRY_COUNT") {
				cin >> par;
			}
			params.push_back(par);
			n--;
		}
	}

	/*
	 for (const auto &val : commands) {
	 cout << val << ' ';
	 }
	 cout << endl;

	 for (const auto &val : params) {
	 cout << val << ' ';
	 }
	 cout << endl;
	 */

	for (int i = 0; i < numberOfCommands; ++i) {
		CommandHandler(queue, commands, params, i);
	}

	/*

	 vector<bool> queue2;
	 int numberOfCommands2 = 8;
	 vector<string> commands2 = { "COME", "WORRY", "WORRY", "COME",
	 "WORRY_COUNT", "COME", "WORRY", "WORRY_COUNT" };
	 vector<int> params2 = { 5, 1, 4, -2, 0, 3, 3, 0 };

	 {
	 cout << "command vect size: " << commands2.size() << endl;
	 for (const auto &val : commands2) {
	 cout << val << ' ';
	 }
	 cout << endl;
	 }

	 {
	 cout << "param vect size: " << params2.size() << endl;

	 for (const auto &val : params2) {
	 cout << val << ' ';
	 }
	 cout << endl;
	 }

	 for (int i = 0; i < numberOfCommands2; ++i) {
	 CommandHandler(queue2, commands2, params2, i);
	 }
	 */
	return 0;
}
