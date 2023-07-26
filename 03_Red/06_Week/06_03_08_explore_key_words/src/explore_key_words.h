#pragma once

#include <iostream>
#include <map>
#include <string>
#include <set>
#include <cctype>
#include <string_view>
#include <future>
#include <functional>
#include <deque>


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
    deque <IteratorRange<Iterator>> pages;
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
    Stats result;
    size_t pos = 0;

    const size_t pos_end = line.npos;
    while (true) {
        size_t space_pos = line.find(' ', pos);
        string find_word = space_pos == pos_end ? line.substr(pos) : line.substr(pos, space_pos - pos);
        if (key_words.count(find_word)) {
            result.word_frequences[move(find_word)] += 1;
        }
        if (space_pos == pos_end) {
            break;
        } else {
            pos = space_pos + 1;
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

template <typename ContainerOfString>
Stats ExploreKeyWordsSingleThreadFromPage(const set<string>& key_words, const ContainerOfString& page) {
    Stats result;
    for (const auto& str : page) {
        result += ExploreLine(key_words, str);
    }
    return result;
}

Stats ExploreKeyWords(const set<string>& key_words, istream& input) {

    vector<string> input_strings;
    for (string line; getline(input, line);input_strings.push_back(move(line))) {}

    const size_t thread_count = input_strings.size() < THREAD_COUNT ? 1 : THREAD_COUNT;
    const size_t page_size = input_strings.size() / thread_count;

    vector<future<Stats>> futures_stats;
    // const auto P = Paginate(input_strings, page_size);
    for (const auto& page : Paginate(input_strings, page_size)) {
        // futures_stats.push_back(async(ExploreKeyWordsSingleThreaFromPage, ref(key_words), ref(page)));
        futures_stats.push_back(async([&key_words, &page] { return ExploreKeyWordsSingleThreadFromPage(key_words, page); }));
        // result += ExploreKeyWordsSingleThreaFromPage(key_words, page);
    }

    Stats result;
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