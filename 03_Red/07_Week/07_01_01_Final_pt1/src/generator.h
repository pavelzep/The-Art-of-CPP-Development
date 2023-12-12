// #include <fstream>

#include <random>
#include <vector>
#include <sstream>
#include <iostream>

#define FIRST_CHAR 97 // 'a'
#define LAST_CHAR 122 // 'z'

#define MIN_WORD_LENTH 1
#define MAX_WORD_LENTH 100
#define WORD_COUNT 10000

#define MIN_WORD_NUMBER 1
#define MAX_WORD_NUMBER WORD_COUNT

#define MIN_DOC_SIZE 1
#define MAX_DOC_SIZE 50
#define DOC_COUNT 5000

#define MIN_QUERY_SIZE 1
#define MAX_QUERY_SIZE 10
#define QUERY_COUNT 5000 

// vector <string> generateWords(
//     size_t min_word_lenth, size_t max_word_lent,
//     size_t first_char, size_t last_char,
//     size_t _word_count);

// vector <string> generateWords(
//     size_t min_word_lenth, size_t max_word_lent,
//     size_t first_char, size_t last_char,
//     size_t _word_count);

// stringstream generateDocuments(
//     size_t _doc_count, const vector <string>& words,
//     size_t min_doc_size, size_t max_doc_size,
//     size_t min_word_number, size_t max_word_number);

using namespace std;

vector <string> generateWords(
    size_t min_word_lenth, size_t max_word_lent,
    size_t first_char, size_t last_char,
    size_t _word_count) {

    random_device random_device;
    mt19937 generator(random_device());
    uniform_int_distribution<> generator_word_lenth(min_word_lenth, max_word_lent);
    uniform_int_distribution<> generator_char(first_char, last_char);

    int word_count = _word_count;
    vector<string> words;
    words.reserve(word_count);

    while (word_count) {
        int current_word_lenth = generator_word_lenth(generator);
        stringstream ss_word;
        while (current_word_lenth) {
            char ch = generator_char(generator);
            ss_word << ch;
            --current_word_lenth;
        }
        words.push_back(ss_word.str());
        --word_count;
    }
    return words;
}

stringstream generateDocuments(
    size_t _doc_count, const vector <string>& words,
    size_t min_doc_size, size_t max_doc_size,
    size_t min_word_number, size_t max_word_number) {

    random_device random_device;
    mt19937 generator(random_device());
    uniform_int_distribution<> generator_doc_size(min_doc_size, max_doc_size);
    uniform_int_distribution<> generator_word_number(min_word_number, max_word_number);

    int doc_count = _doc_count;
    stringstream ss_docs;

    while (doc_count) {
        stringstream ss_doc;
        int doc_size = generator_doc_size(generator);
        while (doc_size) {
            int word_number = generator_word_number(generator) - 1;
            ss_doc << words[word_number] << ' ';
            --doc_size;
        }
        ss_docs << ss_doc.str() << '\n';
        --doc_count;
    }

    return ss_docs;
}

stringstream generateQueries(size_t _query_count, const vector <string>& words,
    size_t min_query_size, size_t max_query_size,
    size_t min_word_number, size_t max_word_number) {

    random_device random_device;
    mt19937 generator(random_device());
    uniform_int_distribution<> generator_query_size(min_query_size, max_query_size);
    uniform_int_distribution<> generator_word_number(min_word_number, max_word_number);

    int query_count = _query_count;
    stringstream ss_queries;

    while (query_count) {
        stringstream ss_query;
        int query_size = generator_query_size(generator);
        while (query_size) {
            int word_number = generator_word_number(generator) - 1;
            ss_query << words[word_number] << ' ';
            --query_size;
        }
        ss_queries << ss_query.str() << '\n';
        --query_count;
    }

    return ss_queries;
}