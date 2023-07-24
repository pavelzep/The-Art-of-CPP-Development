#pragma once

#include <map>
#include <string>
#include <set>

using namespace std;

struct Stats {
    map<string, int> word_frequences;
    void operator += (const Stats& other);
};

Stats ExploreLine(const set<string>& key_words, const string& line) {
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
}