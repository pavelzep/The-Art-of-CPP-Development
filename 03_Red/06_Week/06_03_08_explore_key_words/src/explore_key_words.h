#pragma once

#include <map>
#include <string>
#include <set>
#include <cctype>
#include <string_view>


using namespace std;

struct Stats {
    map<string, int> word_frequences;
    void operator += (const Stats& other);
};

Stats ExploreLine(const set<string>& key_words, const string& line) {

    /*
    size_t pos = 0;
    for (const auto& key : key_words) {
        n = line.find(key, pos);
        if (n != string::npos) {
            size_t t = n + key.size();
            if(isspace(line[t].)){
            }
        }
    }
    */
    Stats result;
    for (const auto& key : key_words) {
        string_view find_words;
        string_view key_view = key;
        size_t pos = 0;
        const size_t pos_end = line.npos;
        while (true) {
            size_t space_pos = line.find(' ', pos);
            find_words = space_pos == pos_end ? line.substr(pos) : line.substr(pos, space_pos - pos);
            if (find_words == key_view) {
                result.word_frequences[key] += 1;
            }

            if (space_pos == pos_end) {
                break;
            } else {
                pos = space_pos + 1;
            }
        }

    }
    return result;
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

    


    return ExploreKeyWordsSingleThread(key_words, input);
}

void Stats::operator+=(const Stats& other) {
    for (auto& item : other.word_frequences) {
        word_frequences[item.first] += item.second;
    }
}