#include <iostream>
#include <sstream>
#include <fstream>
#include "learner.h"
#include "profile.h"

using namespace std;

int main() {

    fstream cin("input.txt");
    Learner learner;
    string line;
    {
        LOG_DURATION("input");
        while (getline(cin, line)) {
            vector<string> words;
            stringstream ss(line);
            string word;
            while (ss >> word) {
                words.push_back(word);
            }
            cout << learner.Learn(words) << "\n";
        }
        cout << "=== known words ===\n";
    }
    {
        LOG_DURATION("output");
        for (auto word : learner.KnownWords()) {
            cout << word << "\n";
        }
    }
}