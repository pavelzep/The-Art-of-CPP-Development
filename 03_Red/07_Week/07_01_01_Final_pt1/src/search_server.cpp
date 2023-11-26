#include "global.h"
#ifdef ORIGIN
#include"original_server.cpp"

#else 

#include "search_server.h"
#include "iterator_range.h"
#include "profile.h"


#include <algorithm>
#include <iterator>
#include <sstream>
#include <iostream>
#ifdef USE_STRING_VIEW
#include <string_view>
#endif


InvertedIndex::InvertedIndex() {
    // docs.resize(50000);
    // docs.reserve(50000);
}

// void InvertedIndex::Add(const string& document, size_t docid) {
//     for (const auto word : SplitIntoWords(document)) {
//         docs[docid] = word;
//         index[docs[docid]].push_back(docid);
//     }
// }

void InvertedIndex::Add(const string& document) {
    // docs.push_back(document);

    const size_t docid = docs_count;
    for (const auto& word : SplitIntoWords(document)) {
        // doc_to_count_t doc_to_count;
        // doc_to_count[]
        index[word][docid]++;
    }
    docs_count++;
}

size_t InvertedIndex::GetDocsCount() const {
    return docs_count;
}

const doc_to_word_count_t InvertedIndex::Lookup(const string& word) const {
    if (auto it = index.find(word); it != index.end()) {
        return it->second;
    } else {
        return {};
    }
}

vector<string> SplitIntoWords(const string& line) {
    istringstream words_input(line);
    return { istream_iterator<string>(words_input), istream_iterator<string>() };
}

#ifdef USE_STRING_VIEW
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
#endif

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

#ifdef USE_STRING_VIEW
vector<string_view> SearchServer::Split(string_view line, TotalDuration& dest) {
    ADD_DURATION(dest);
    return SplitIntoWordsView(line);
}
#endif

vector<string> SearchServer::Split(string& line, TotalDuration& dest) {
    ADD_DURATION(dest);
    return SplitIntoWords(line);
}

#ifndef USE_PAIR
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
#endif

#define pt1
#define pt2
#define pt3
#define pt4
#define pt5
#define pt6
#define pt7

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
#ifdef pt6
    TotalDuration Clean_d("Clean Duration");
#endif
#ifdef pt7
    TotalDuration Resize_d("Resize Duration");
#endif

    size_t doc_count = index.GetDocsCount();
    vector<docid_to_hitcount> docid_count;
    vector<docid_to_hitcount> search_results;

    for (string current_query; getline(query_input, current_query); ) {
#ifdef pt7
        {
            ADD_DURATION(Resize_d);
            docid_count.reserve(doc_count);
        }
#endif

#ifdef pt1
        const auto words = Split(current_query, Split_d);
#endif

#ifdef pt2
        {
            ADD_DURATION(Lookup_d);
            {
                for (const auto& word : words) {

                    for (const auto& doc_to_word_count : index.Lookup(word)) {
#ifdef USE_PAIR 
                        docid_count[doc_to_word_count.first].first = doc_to_word_count.first;
                        docid_count[doc_to_word_count.first].second += doc_to_word_count.second;
#else 
                        // docid_count.push_back
                        docid_count[doc_to_word_count.first].docid = doc_to_word_count.first;
                        docid_count[doc_to_word_count.first].hitcount += doc_to_word_count.second;
#endif
                    }
                }
            }
        }

#endif

#ifdef pt3    
        search_results.reserve(docid_count.size());
        {
            ADD_DURATION(GetRes_d);
            {
                for (auto& item : docid_count) {
#ifdef USE_PAIR 
                    if (item.second) search_results.push_back(move(item));
#else
                    if (item.hitcount) search_results.push_back(move(item));
#endif
                }
            }
        }
#endif

#ifdef pt4
        {
            ADD_DURATION(Sort_d);
            {
                size_t offset = search_results.size() > 5 ? 5 : search_results.size();
                partial_sort(
                    begin(search_results),
                    begin(search_results) + offset,
                    end(search_results),
                    [](const docid_to_hitcount& lhs, const docid_to_hitcount& rhs) {
#ifdef USE_PAIR
                        int64_t lhs_docid = lhs.first;
                        auto lhs_hit_count = lhs.second;
                        int64_t rhs_docid = rhs.first;
                        auto rhs_hit_count = rhs.second;
                        return make_pair(lhs_hit_count, -lhs_docid) > make_pair(rhs_hit_count, -rhs_docid);
#else
                        return lhs > rhs;
#endif
                    }
                );
            }
        }
#endif

#ifdef pt5
        {
            ADD_DURATION(Output_d);
            {
                search_results_output << current_query << ':';
                for (auto& [docid, hitcount] : Head(search_results, 5)) {
                    if (!hitcount) { break; }
                    search_results_output << " {"
                        << "docid: " << docid << ", "
                        << "hitcount: " << hitcount << '}';
                }
            }
        }
        search_results_output << endl;
#endif
#ifdef pt6
        {
            ADD_DURATION(Clean_d);
            search_results.resize(0);
            docid_count.resize(0);
        }
#endif    

    }
}

#endif