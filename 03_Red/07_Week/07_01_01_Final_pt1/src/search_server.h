#pragma once

#include "global.h"

#include <istream>
#include <ostream>
#include <set>
#include <list>
#include <vector>
#include <map>
#include <string>

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

    Split() {
        vector<string> SplitIntoWords(const string & line, TotalDuration & dest) {
            ADD_DURATION(dest);
            istringstream words_input(line);
            return { istream_iterator<string>(words_input), istream_iterator<string>() };
        }
    };
};

#else

vector<string> SplitIntoWords(const string& line);

class InvertedIndex {
public:
    void Add(const string& document, size_t docid);
    list<size_t> Lookup(const string& word) const;

private:
    map<string, list<size_t>> index;


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
#endif