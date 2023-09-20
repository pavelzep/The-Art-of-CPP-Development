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

#ifdef ORIGIN

vector<string> SplitIntoWords(const string& line);

class InvertedIndex {
public:
    void Add(const string& document);
    list<size_t> Lookup(const string& word) const;
    const string& GetDocument(size_t id) const { return docs[id]; }
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
};

#else

vector<string> SplitIntoWords(const string& line);
vector<string_view> SplitIntoWordsView(string_view line);

class InvertedIndex {
public:
    void Add(const string& document, size_t docid);
    list<size_t> Lookup(const string& word) const;
    list<size_t> Lookup(const string_view& word) const;

private:
    map<string_view, list<size_t>> index;

};

class SearchServer {
public:
    SearchServer() = default;
    explicit SearchServer(istream& document_input);
    void UpdateDocumentBase(istream& document_input);
    void AddQueriesStream(istream& query_input, ostream& search_results_output);

private:
    InvertedIndex index;

    vector<string_view> Split(string_view line, TotalDuration& dest);

};


#endif