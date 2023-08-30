#pragma once

#include <istream>
#include <ostream>
#include <set>
#include <list>
#include <vector>
#include <map>
#include <string>

// #define ORIGIN

using namespace std;

class InvertedIndex {
public:
    void Add(const string& document);
    list<size_t> Lookup(const string& word) const;

#ifdef ORIGIN
    const string& GetDocument(size_t id) const {
        return docs[id];
    }
#else
    InvertedIndex() :docid(0) {}
#endif

private:
    map<string, list<size_t>> index;
    
#ifdef ORIGIN
    vector<string> docs;
#else
    size_t docid;
#endif
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
