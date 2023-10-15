
#include "search_server.h"
#include "iterator_range.h"
#include "profile.h"


#include <algorithm>
#include <iterator>
#include <sstream>
#include <iostream>
#include <string_view>


#ifdef ORIGIN

vector<string> SplitIntoWords(const string& line) {
    istringstream words_input(line);
    return { istream_iterator<string>(words_input), istream_iterator<string>() };
}

SearchServer::SearchServer(istream& document_input) {
    UpdateDocumentBase(document_input);
}

void SearchServer::UpdateDocumentBase(istream& document_input) {
    InvertedIndex new_index;
    for (string current_document; getline(document_input, current_document); ) {
        new_index.Add(move(current_document));
    }
    index = move(new_index);
}


void SearchServer::AddQueriesStream(istream& query_input, ostream& search_results_output) {
    for (string current_query; getline(query_input, current_query); ) {
        const auto words = SplitIntoWords(current_query);

        map<size_t, size_t> docid_count;
        for (const auto& word : words) {
            for (const size_t docid : index.Lookup(word)) {
                docid_count[docid]++;
            }
        }

        vector<pair<size_t, size_t>> search_results(
            docid_count.begin(), docid_count.end()
        );
        sort(
            begin(search_results),
            end(search_results),
            [](pair<size_t, size_t> lhs, pair<size_t, size_t> rhs) {
                int64_t lhs_docid = lhs.first;
                auto lhs_hit_count = lhs.second;
                int64_t rhs_docid = rhs.first;
                auto rhs_hit_count = rhs.second;
                return make_pair(lhs_hit_count, -lhs_docid) > make_pair(rhs_hit_count, -rhs_docid);
            }
        );

        search_results_output << current_query << ':';
        for (auto [docid, hitcount] : Head(search_results, 5)) {
            search_results_output << " {"
                << "docid: " << docid << ", "
                << "hitcount: " << hitcount << '}';
        }
        search_results_output << endl;
    }

}

void InvertedIndex::Add(const string& document) {
    docs.push_back(document);
    const size_t docid = docs.size() - 1;
    for (const auto& word : SplitIntoWords(document)) {
        index[word].push_back(docid);
    }
}

list<size_t> InvertedIndex::Lookup(const string& word) const {
    if (auto it = index.find(word); it != index.end()) {
        return it->second;
    } else {
        return {};
    }
}


#else 

vector<string> SplitIntoWords(const string& line) {
    istringstream words_input(line);
    return { istream_iterator<string>(words_input), istream_iterator<string>() };
}
vector <string_view> SplitIntoWordsView(string_view str) {
    vector <string_view > result;
    while (true) {
        size_t space = str.find(' ');
        result.push_back(str.substr(0, space));
        if (space == str.npos) {
            break;
        } else {
            str.remove_prefix(space + 1);
        }
    }
    return result;
}


SearchServer::SearchServer(istream& document_input) {
    UpdateDocumentBase(document_input);
}

void SearchServer::UpdateDocumentBase(istream& document_input) {
    InvertedIndex new_index;
    size_t docid = 0;
    for (string current_document; getline(document_input, current_document); ) {

        new_index.Add(move(current_document), docid++);

    }

    index = move(new_index);
}

vector<string_view> SearchServer::Split(string_view line, TotalDuration& dest) {
    ADD_DURATION(dest);
    return SplitIntoWordsView(line);
}

vector<string> SearchServer::Split(string& line, TotalDuration& dest) {
    ADD_DURATION(dest);
    return SplitIntoWords(line);
}


#define pt1
#define pt2
// #define pt3
#define pt4
#define pt5

void SearchServer::AddQueriesStream(istream& query_input, ostream& search_results_output) {
#ifdef pt1
    TotalDuration Split_d("Split Duration");
#endif
#ifdef pt2
    TotalDuration Lookup_d("Lookup Duration");
#endif
#ifdef pt3
    TotalDuration GetRes_d("GetRes Duration");
#endif
#ifdef pt4
    TotalDuration Sort_d("Sort Duration");
#endif
#ifdef pt5
    TotalDuration Output_d("Output Duration");
#endif


    // vector<size_t> docid_count(50000);
    vector<pair<size_t, size_t>> search_results(50000);
    // map<size_t, size_t> docid_count;

    for (string current_query; getline(query_input, current_query); ) {
        search_results.clear();

        //pt1
#ifdef pt1
        const auto words = Split(current_query, Split_d);
#endif
        //pt2
#ifdef pt2
        // map<size_t, size_t> docid_count;
        {
            ADD_DURATION(Lookup_d);
            {
                for (const auto& word : words) {
                    for (const size_t docid : index.Lookup(word)) {
                        search_results[docid].first = docid;
                        search_results[docid].second++;
                    }
                }
            }
        }
#endif

#ifdef pt3
        //pt3    
        vector<pair<size_t, size_t>> search_results;
        {
            ADD_DURATION(GetRes_d);
            {

                search_results = vector<pair<size_t, size_t>>(docid_count.begin(), docid_count.end());
            }
        }
#endif

#ifdef pt4
        //pt4
        {
            ADD_DURATION(Sort_d);
            {
                // partial_sort(begin(docid_count), begin(docid_count) + 5, end(docid_count));

                partial_sort(
                    begin(search_results),
                    begin(search_results) + 5,
                    end(search_results),
                    [](pair<size_t, size_t> lhs, pair<size_t, size_t> rhs) {
                        int64_t lhs_docid = lhs.first;
                        auto lhs_hit_count = lhs.second;
                        int64_t rhs_docid = rhs.first;
                        auto rhs_hit_count = rhs.second;
                        return make_pair(lhs_hit_count, -lhs_docid) > make_pair(rhs_hit_count, -rhs_docid);
                    }
                );
            }
        }
#endif

#ifdef pt5
        //pt5
        {
            ADD_DURATION(Output_d);
            {
                search_results_output << current_query << ':';
                for (auto [docid, hitcount] : Head(search_results, 5)) {
                    search_results_output << " {"
                        << "docid: " << docid << ", "
                        << "hitcount: " << hitcount << '}';
                }
            }
        }
        search_results_output << endl;
        search_results_output.
#endif
    }
}

InvertedIndex::InvertedIndex() {
    docs.reserve(50000);
}

void InvertedIndex::Add(const string& document, size_t docid) {
    for (const auto word : SplitIntoWords(document)) {
        docs[docid] = word;
        index[docs[docid]].push_back(docid);
    }
}

list<size_t> InvertedIndex::Lookup(const string& word) const {
    if (auto it = index.find(word); it != index.end()) {
        return it->second;
    } else {
        return {};
    }
}

#endif