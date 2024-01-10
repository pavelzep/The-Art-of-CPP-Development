#pragma once

#include "global.h"
#include "synchronized.h"

#include <istream>
#include <ostream>
#include <set>
#include <vector>
#include <map>
#include <string>

using namespace std;
using docid_t = size_t;
using hitcount_t = size_t;

struct docid_to_hitcount {
    docid_t docid;
    hitcount_t hitcount;
};

vector<string> SplitIntoWords(const string& line);

class InvertedIndex {
public:
    InvertedIndex();
    void Add(const string& document);
    const vector<docid_to_hitcount>& Lookup(const string& word) const;
    const docid_t GetDocsCount() const;

private:
    map <string, vector <docid_to_hitcount>> index;
    docid_t docs_count = 0;
};

class SearchServer {
public:
    SearchServer() = default;
    explicit SearchServer(istream& document_input);
    void UpdateDocumentBase(istream& document_input);
    void AddQueriesStream(istream& query_input, ostream& search_results_output);

private:
    Synchronized<InvertedIndex> s_index;
    // InvertedIndex index;
};