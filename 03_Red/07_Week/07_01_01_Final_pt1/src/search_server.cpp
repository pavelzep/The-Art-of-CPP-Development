
#include "search_server.h"
#include "iterator_range.h"
#include "profile.h"


#include <algorithm>
#include <iterator>
#include <sstream>
#include <iostream>


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

vector<string> SearchServer::Split(const string& line, TotalDuration& dest) {
    ADD_DURATION(dest);
    return SplitIntoWords(line);
}

map<size_t, size_t> SearchServer::Lookup(InvertedIndex& index, const vector<string>& words, TotalDuration& dest) {
    map<size_t, size_t> docid_count;
    ADD_DURATION(dest);
    for (const auto& word : words) {
        for (const size_t docid : index.Lookup(word)) {
            docid_count[docid]++;
        }
    }
    return docid_count;
}

void SearchServer::Lookup(map<size_t, size_t>& docid_count, InvertedIndex& index, const vector<string>& words, TotalDuration& dest) {

    ADD_DURATION(dest);
    for (const auto& word : words) {
        for (const size_t docid : index.Lookup(word)) {
            docid_count[docid]++;
        }
    }
}

vector<pair<size_t, size_t>> SearchServer::GetResult(const map<size_t, size_t>& docid_count, TotalDuration& dest) {
    ADD_DURATION(dest);
    return vector<pair<size_t, size_t>>(docid_count.begin(), docid_count.end());

}

void SearchServer::AddQueriesStream(istream& query_input, ostream& search_results_output) {
    TotalDuration Split_d("Split Duration");
    TotalDuration Lookup_d("Lookup Duration");
    TotalDuration GetRes_d("GetRes Duration");
    TotalDuration Sort_d("Sort Duration");
    TotalDuration Output_d("Output Duration");

    for (string current_query; getline(query_input, current_query); ) {

        //pt1
        const auto words = Split(current_query, Split_d);

        //pt2
        // map<size_t, size_t> docid_count;
        // Lookup(docid_count, index, words, Lookup_d);
        map<size_t, size_t> docid_count = Lookup(index, words, Lookup_d);

        //pt3        
        vector<pair<size_t, size_t>> search_results = GetResult(docid_count, GetRes_d);

        //pt4
        {
            ADD_DURATION(Sort_d);
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

        }

        //pt5
        {
            ADD_DURATION(Output_d);
            search_results_output << current_query << ':';
            for (auto [docid, hitcount] : Head(search_results, 5)) {
                search_results_output << " {"
                    << "docid: " << docid << ", "
                    << "hitcount: " << hitcount << '}';
            }

        }
        search_results_output << endl;
    }
}

void InvertedIndex::Add(const string& document, size_t docid) {
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
#endif
