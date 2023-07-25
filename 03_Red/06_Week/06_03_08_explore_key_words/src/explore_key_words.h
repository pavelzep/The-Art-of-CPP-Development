#pragma once

#include <map>
#include <string>
#include <set>
#include <cctype>
#include <string_view>
#include <future>
#include <functional>
#define THREAD_COUNT 4


using namespace std;




template<typename Iterator>
class IteratorRange {
private:
    Iterator first, last;
public:
    IteratorRange(Iterator f, Iterator l)
        : first(f)
        , last(l) {
    }
    Iterator begin() const { return first; }
    Iterator end() const { return last; }
    size_t size() const { return end() - begin(); }
};

template <typename Iterator>
class Paginator {
private:
    vector <IteratorRange<Iterator>> pages;
public:
    Paginator(Iterator begin, Iterator end, size_t page_size) {
        for (Iterator it = begin;it < end;it = next(it, page_size)) {
            IteratorRange page(it, min(next(it, page_size), end));
            pages.push_back(page);
        }
    }
    size_t size() const { return pages.size(); }
    auto begin() const { return pages.begin(); }
    auto end() const { return pages.end(); }
};

template <typename Container>
auto Paginate(Container& container, size_t page_size) {
    return Paginator(container.begin(), container.end(), page_size);
};






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

    // futures_stats.push_back(async(ExploreKeyWordsSingleThread, key_words, input));
    Stats result;
    vector<future<Stats>> futures_stats;
    const size_t thread_count = key_words.size() < 4 ? 1 : THREAD_COUNT;
    const size_t page_size = key_words.size() / thread_count;

    for (const auto page : Paginate(key_words, page_size)) {
        futures_stats.push_back(async(ExploreKeyWordsSingleThread, ref(key_words), ref(input)));
    }


    for (auto& item : futures_stats) {
        result += item.get();
    }
    return result;
    // return async(ExploreKeyWordsSingleThread, ref(key_words), ref(input)).get();
}

void Stats::operator+=(const Stats& other) {
    for (auto& item : other.word_frequences) {
        word_frequences[item.first] += item.second;
    }
}