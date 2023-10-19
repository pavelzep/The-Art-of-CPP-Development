#pragma once

#include "global.h"

#include <istream>
#include <ostream>
#include <set>
#include <list>
#include <vector>
#include <map>
#include <string>
#include <string_view>

#include "profile.h"

using namespace std;

vector<string> SplitIntoWords(const string& line);


#ifndef ORIGIN
vector<string_view> SplitIntoWordsView(string_view line);
#endif

class InvertedIndex {
public:
    InvertedIndex();
    void Add(const string& document, size_t docid);
    list<size_t> Lookup(const string& word) const;

private:
    map<string, list<size_t>> index;
    vector<string> docs;
};

class SearchServer {
public:
    SearchServer() = default;
    explicit SearchServer(istream& document_input);
    void UpdateDocumentBase(istream& document_input);
    void AddQueriesStream(istream& query_input, ostream& search_results_output);

private:
    InvertedIndex index;
    #ifndef ORIGIN
    vector<string_view> Split(string_view line, TotalDuration& dest);
    vector<string> Split(string& line, TotalDuration& dest);
    #endif
};