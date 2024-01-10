#include "global.h"


#include "search_server.h"
#include "iterator_range.h"
#include "profile.h"


#include <algorithm>
#include <iterator>
#include <sstream>
#include <iostream>

InvertedIndex::InvertedIndex() {}

const docid_t InvertedIndex::GetDocsCount() const {
    return docs_count;
}


void InvertedIndex::Add(const string& document) {
    for (const auto& word : SplitIntoWords(document)) {
        vector<docid_to_hitcount>& word_docs = index[word];
        if (word_docs.empty()) {
            word_docs.push_back({ docs_count, 1 });
        } else if (word_docs.back().docid == docs_count) {
            ++word_docs.back().hitcount;
        } else {
            word_docs.push_back({ docs_count, 1 });
        }
    }
    ++docs_count;
}

const vector<docid_to_hitcount>& InvertedIndex::Lookup(const string& word) const {
    static vector<docid_to_hitcount> empty;
    if (auto it = index.find(word); it != index.end()) {
        return it->second;
    } else {
        return empty;
    }
}

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

bool operator > (const docid_to_hitcount& lhs, const  docid_to_hitcount& rhs) {
    if (lhs.hitcount == rhs.hitcount) {
        if (-(int32_t)lhs.docid > -(int32_t)rhs.docid)
            return true;
        else
            return false;
    } else
        if (lhs.hitcount > rhs.hitcount)
            return true;
        else
            return false;
}

#ifdef DURATION_PARTS

#define pt1
#define pt2
#define pt3
#define pt4
#define pt5

#endif

void SearchServer::AddQueriesStream(istream& query_input, ostream& search_results_output) {

#ifdef DURATION_PARTS
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

#endif

    docid_t doc_count = index.GetDocsCount();
    vector<hitcount_t> doc_hitcounts(doc_count, 0);
    vector<docid_to_hitcount> search_results;
    docid_t min_id = doc_count;
    docid_t max_id = 0;


    for (string current_query; getline(query_input, current_query); ) {


        vector<string> words;
        {
#ifdef pt1
            ADD_DURATION(Split_d);
#endif
            words = SplitIntoWords(current_query);
        }



        {
#ifdef pt2
            ADD_DURATION(Lookup_d);
#endif
            for (const auto& word : words) {
                for (const auto doc_hitcount : index.Lookup(word)) {
                    if (doc_hitcount.hitcount) {
                        doc_hitcounts[doc_hitcount.docid] += doc_hitcount.hitcount;
                        min_id = min(min_id, doc_hitcount.docid);
                        max_id = max(max_id, doc_hitcount.docid);
                    }
                }
            }
        }

        {
#ifdef pt3   
            ADD_DURATION(GetRes_d);
#endif
            search_results.clear();
            {
                for (docid_t id = min_id; id <= max_id; ++id) {
                    if (doc_hitcounts[id]) {
                        search_results.push_back({ id, doc_hitcounts[id] });
                        doc_hitcounts[id] = 0;
                    }
                }
            }
            max_id = 0;
            min_id = doc_count;
        }

        {
#ifdef pt4
            ADD_DURATION(Sort_d);
#endif
            size_t offset = search_results.size() > 5 ? 5 : search_results.size();
            partial_sort(
                begin(search_results),
                begin(search_results) + offset,
                end(search_results),
                [](const docid_to_hitcount& lhs, const docid_to_hitcount& rhs) {
                    return lhs > rhs;
                }
            );
        }



        {
#ifdef pt5
            ADD_DURATION(Output_d);
#endif
            search_results_output << current_query << ':';
            for (auto& [docid, hitcount] : Head(search_results, 5)) {
                if (!hitcount) { break; }
                search_results_output << " {"
                    << "docid: " << docid << ", "
                    << "hitcount: " << hitcount << '}';
            }
        }
        search_results_output << endl;
    }
}