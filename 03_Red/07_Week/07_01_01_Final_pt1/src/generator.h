#include <fstream>
#include <random>
#include <vector>
#include <sstream>
#include <iostream>

using namespace std;





#define FIRST_CHAR 97 // 'a'
#define LAST_CHAR 122 // 'z'

#define MIN_WORD_LENTH 1
#define MAX_WORD_LENTH 100
#define WORD_COUNT 10000

#define MIN_WORD_NUMBER 1
#define MAX_WORD_NUMBER WORD_COUNT

#define MIN_DOC_SIZE 1
#define MAX_DOC_SIZE 50
#define DOC_COUNT 50000

#define MIN_QUERY_SIZE 1
#define MAX_QUERY_SIZE 10
#define QUERY_COUNT 50000 

vector<char> chars = { 'a','b' };


//1 сгенерировать длинну слова от 1 до 100

// сгенерировать слово взять буквы из массисива букв 


int main() {


    random_device random_device;
    mt19937 generator(random_device());
    uniform_int_distribution<> generator_word_lenth(MIN_WORD_LENTH, MAX_WORD_LENTH);
    uniform_int_distribution<> generator_char(FIRST_CHAR, LAST_CHAR);
    uniform_int_distribution<> generator_doc_size(MIN_DOC_SIZE, MAX_DOC_SIZE);
    uniform_int_distribution<> generator_query_size(MIN_QUERY_SIZE, MAX_QUERY_SIZE);
    uniform_int_distribution<> generator_word_number(MIN_WORD_NUMBER, MAX_WORD_NUMBER);

    ofstream output1("docs.txt");
    ofstream output2("queries.txt");

    // генерируем 10000 слов
    int word_count = WORD_COUNT;
    vector<string> words;
    words.reserve(10000);
    while (word_count) {
        int current_word_lenth = generator_word_lenth(generator);
        stringstream ss_word;
        while (current_word_lenth) { // генерируем слово
            char ch = generator_char(generator);
            ss_word << ch;
            --current_word_lenth;
        }
        words.push_back(ss_word.str());
        --word_count;
    }

    // генерируем документы 
    int doc_count = DOC_COUNT;
    stringstream ss_docs;
    while (doc_count) {
        stringstream ss_doc;
        int doc_size = generator_doc_size(generator);
        while (doc_size) { //генерируем 1 документ
            int word_number = generator_word_number(generator) - 1;
            ss_doc << words[word_number] << ' ';
            --doc_size;
        }
        ss_docs << ss_doc.str() << '\n';
        --doc_count;
    }
    output1 << ss_docs.str();


    // генерируем запросы
    int query_count = QUERY_COUNT;
    stringstream ss_queries;
    while (query_count) {
        stringstream ss_query;
        int doc_size = generator_query_size(generator);
        while (doc_size) { //генерируем 1 запрос
            int word_number = generator_word_number(generator) - 1;
            ss_query << words[word_number] << ' ';
            --doc_size;
        }
        ss_queries << ss_query.str() << '\n';
        --query_count;
    }
    output2 << ss_queries.str();


    return 0;
}

#if 0
int main() {
    random_device random_device;
    mt19937 generator(random_device());
    uniform_int_distribution<> distribution(a, b);

    ofstream output("output.txt");
    output << q1 + q2 << '\n';

    while (q1) {
        output << "ADD "
            << distribution(generator) << ' '
            << distribution(generator) << '\n';
        --q1;
    }

    while (q2) {

        output << "GO "
            << distribution(generator) << ' '
            << distribution(generator) << '\n';
        --q2;
    }

    return 0;
}
#endif