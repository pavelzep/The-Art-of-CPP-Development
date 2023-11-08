#pragma once

#include "global.h"

#ifdef ORIGIN
#include"original_server.h"
#else 

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

#ifdef USE_STRING_VIEW
vector<string_view> SplitIntoWordsView(string_view line);
#endif

class InvertedIndex {
public:
    InvertedIndex();

    // void Add(const string& document, size_t docid);
    void Add(const string& document);
    list<size_t> Lookup(const string& word) const;
    size_t GetDocsCount();

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

#ifdef USE_STRING_VIEW
    vector<string_view> Split(string_view line, TotalDuration& dest);
#endif

    vector<string> Split(string& line, TotalDuration& dest);

};
#endif
