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
using docid_t = uint32_t;
using hitcount_t = uint32_t;




#ifdef USE_PAIR
using docid_to_hitcount = pair <docid_t, hitcount_t>;
#else
struct docid_to_hitcount {
    docid_t docid;
    hitcount_t hitcount;
};
#endif

// using doc_to_word_count_t = map <docid_t, hitcount_t>;
using docsid_to_hitcounts_t = vector <docid_to_hitcount>;

vector<string> SplitIntoWords(const string& line);

#ifdef USE_STRING_VIEW
vector<string_view> SplitIntoWordsView(string_view line);
#endif

class InvertedIndex {
public:
    InvertedIndex();
    void Add(const string& document);
    const docsid_to_hitcounts_t& Lookup(const string& word, const docsid_to_hitcounts_t& res) const;
    size_t GetDocsCount()const;

private:
    //map <string, map <docid_t, hitcount_t>> index;
    map <string, docsid_to_hitcounts_t> index;

    docid_t docs_count = 0;
};

class SearchServer {
public:
    SearchServer() = default;
    explicit SearchServer(istream& document_input);
    void UpdateDocumentBase(istream& document_input);
    void AddQueriesStream(istream& query_input, ostream& search_results_output);

private:
    InvertedIndex index;
    vector<string> Split(string& line, TotalDuration& dest);

#ifdef USE_STRING_VIEW
    vector<string_view> Split(string_view line, TotalDuration& dest);
#endif

};
#endif
