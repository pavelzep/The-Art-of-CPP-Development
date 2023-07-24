#pragma once

#include <map>
#include <string>
#include <set>
#include <cctype>


using namespace std;

struct Stats {
    map<string, int> word_frequences;
    void operator += (const Stats& other);
};

Stats ExploreLine(const set<string>& key_words, const string& line) {
    size_t pos = 0
        for (const auto& key : key_words) {
            n = line.find(key, pos);
            if (n != string::npos) {
                size_t t = n + key.size();
                if(isspace(line[t].)){
                    
                }
            }

        }
    Stats();
}

Stats ExploreKeyWordsSingleThread(
    const set<string>& key_words, istream& input
) {
    Stats result;
    for (string line; getline(input, line); ) {
        result += ExploreLine(key_words, line);
    }
    return result;
}

Stats ExploreKeyWords(const set<string>& key_words, istream& input) {
    // Реализуйте эту функцию
    Stats();
}

void Stats::operator+=(const Stats& other) {
}