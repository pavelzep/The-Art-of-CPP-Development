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
    docs.reserve(50000);
}

// void InvertedIndex::Add(const string& document, size_t docid) {
//     for (const auto word : SplitIntoWords(document)) {
//         docs[docid] = word;
//         index[docs[docid]].push_back(docid);
//     }
// }

void InvertedIndex::Add(const string& document) {
    docs.push_back(document);

    const size_t docid = docs.size() - 1;
    for (const auto& word : SplitIntoWords(document)) {
        // doc_to_count_t doc_to_count;
        // doc_to_count[]
        index[word][docid]++;
    }
}

size_t InvertedIndex::GetDocsCount() {
    return docs.size();
}

/*list<size_t>*/
doc_to_word_count_t InvertedIndex::Lookup(const string& word) const {
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
    // size_t docid = 0;
    for (string current_document; getline(document_input, current_document); ) {

        // new_index.Add(move(current_document), docid++);
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

struct docid_to_hitcount {
    size_t docid;
    size_t hitcount;

};

bool operator > (const docid_to_hitcount& lhs, const  docid_to_hitcount& rhs) {
    if (lhs.hitcount == rhs.hitcount) {
        if (-(int64_t)lhs.docid > -(int64_t)rhs.docid)
            return true;
        else
            return false;
    } else
        if (lhs.hitcount > rhs.hitcount)
            return true;
        else
            return false;
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

    // map<size_t, size_t> docid_count;
    // vector<pair<size_t, size_t>> search_results(50000);
    size_t doc_count = index.GetDocsCount();
    vector<docid_to_hitcount> search_results(doc_count);

    for (string current_query; getline(query_input, current_query); ) {

#ifdef pt1
        const auto words = Split(current_query, Split_d);
#endif

#ifdef pt2
        // map<size_t, size_t> docid_count;
        {
            ADD_DURATION(Lookup_d);
            {
                for (const auto& word : words) {
                    
                    // for (const size_t docid : index.Lookup(word)) {
                    //     // search_results[docid].first = docid;
                    //     // search_results[docid].second++;
                    //     search_results[docid].docid = docid;
                    //     search_results[docid].hitcount++;
                    }
                }
            }
        }
#endif

#ifdef pt3    
        vector<pair<size_t, size_t>> search_results;
        {
            ADD_DURATION(GetRes_d);
            {
                search_results = vector<pair<size_t, size_t>>(docid_count.begin(), docid_count.end());
            }
        }
#endif

#ifdef pt4
        {
            ADD_DURATION(Sort_d);
            {
                // partial_sort(begin(docid_count), begin(docid_count) + 5, end(docid_count));
                // partial_sort(
                //     begin(search_results),
                //     begin(search_results) + 5,
                //     end(search_results),
                //     [](pair<size_t, size_t> lhs, pair<size_t, size_t> rhs) {
                //         int64_t lhs_docid = lhs.first;
                //         auto lhs_hit_count = lhs.second;
                //         int64_t rhs_docid = rhs.first;
                //         auto rhs_hit_count = rhs.second;
                //         return make_pair(lhs_hit_count, -lhs_docid) > make_pair(rhs_hit_count, -rhs_docid);
                //     }
                // );
                partial_sort(
                    begin(search_results),
                    begin(search_results) + 5,
                    end(search_results),
                    [](const docid_to_hitcount& lhs, const docid_to_hitcount& rhs) {
                        return lhs > rhs;
                        // int64_t lhs_docid = lhs.docid;
                        // auto lhs_hit_count = lhs.hitcount;
                        // int64_t rhs_docid = rhs.docid;
                        // auto rhs_hit_count = rhs.hitcount;
                        // make_pair(lhs_hit_count, -lhs_docid) > make_pair(rhs_hit_count, -rhs_docid);
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
                    if (!hitcount) { break; }
                    search_results_output << " {"
                        << "docid: " << docid << ", "
                        << "hitcount: " << hitcount << '}';
                }
                // for (size_t i = 0;i < 5;++i) {
                //     if (!search_results[i].hitcount) { break; }
                //     search_results_output << " {"
                //         << "docid: " << search_results[i].docid << ", "
                //         << "hitcount: " << search_results[i].hitcount << '}';
                // }
            }
        }
        search_results_output << endl;
#endif
        for (auto& item : search_results) {
            item.docid = 0;
            item.hitcount = 0;
        }
        // search_results.clear();
    }
}

#endif