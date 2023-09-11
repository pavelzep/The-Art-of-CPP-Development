#pragma once

#include "test_runner.h"
#include "profile.h"

#include "search_server.h"
#include "parse.h"

#include <fstream>

void TestAll();
void TestFunctionality(const vector<string>& docs, const vector<string>& queries, const vector<string>& expected);

void TestSerpFormat();
void TestTop5();
void TestHitcount();
void TestRanking();
void TestBasicSearch();
void TestBasic();
void BigTest();
void BigTest(SearchServer& srv, istream& document_input, istream& query_input, ostream& search_results_output);

void TestFunctionality(
    const vector<string>& docs,
    const vector<string>& queries,
    const vector<string>& expected
) {
    istringstream docs_input(Join('\n', docs));
    istringstream queries_input(Join('\n', queries));

    SearchServer srv;
    srv.UpdateDocumentBase(docs_input);
    ostringstream queries_output;
    srv.AddQueriesStream(queries_input, queries_output);

    const string result = queries_output.str();
    const auto lines = SplitBy(Strip(result), '\n');
    ASSERT_EQUAL(lines.size(), expected.size());
    for (size_t i = 0; i < lines.size(); ++i) {
        ASSERT_EQUAL(lines[i], expected[i]);
    }
}

void TestBasic() {
    const vector<string> docs = {
         "q w e r t y",
         "q w e r t",
         "q w e r"
    };
    const vector<string> queries = { "w", "e", "r" };

    const vector<string> expected = {
          Join(' ', vector{
            "w:",
            "{docid: 0, hitcount: 1}",
            "{docid: 1, hitcount: 1}",
            "{docid: 2, hitcount: 1}"
          }),
          Join(' ', vector{
            "e:",
            "{docid: 0, hitcount: 1}",
            "{docid: 1, hitcount: 1}",
            "{docid: 2, hitcount: 1}"
          }),
          Join(' ', vector{
            "r:",
            "{docid: 0, hitcount: 1}",
            "{docid: 1, hitcount: 1}",
            "{docid: 2, hitcount: 1}"
          }),
    };

    TestFunctionality(docs, queries, expected);
}

void BigTest() {
    SearchServer srv;
    ifstream document_in_stream("../document_input.txt");
    ifstream query_in_stream("../query_input.txt");

    {
        LOG_DURATION("BigTest");
        BigTest(srv, document_in_stream, query_in_stream, cout);
    }
}

void BigTest(SearchServer& srv, istream& document_input, istream& query_input, ostream& search_results_output) {
    srv.UpdateDocumentBase(document_input);
    srv.AddQueriesStream(query_input, search_results_output);
}

void TestSerpFormat() {
    const vector<string> docs = {
      "london is the capital of great britain",
      "i am travelling down the river"
    };
    const vector<string> queries = { "london", "the" };
    const vector<string> expected = {
      "london: {docid: 0, hitcount: 1}",
      Join(' ', vector{
        "the:",
        "{docid: 0, hitcount: 1}",
        "{docid: 1, hitcount: 1}"
      })
    };

    TestFunctionality(docs, queries, expected);
}

void TestTop5() {
    const vector<string> docs = {
      "milk a",
      "milk b",
      "milk c",
      "milk d",
      "milk e",
      "milk f",
      "milk g",
      "water a",
      "water b",
      "fire and earth",

    };

    const vector<string> queries = { "milk", "water", "rock" };
    const vector<string> expected = {
      Join(' ', vector{
        "milk:",
        "{docid: 0, hitcount: 1}",
        "{docid: 1, hitcount: 1}",
        "{docid: 2, hitcount: 1}",
        "{docid: 3, hitcount: 1}",
        "{docid: 4, hitcount: 1}"
      }),
      Join(' ', vector{
        "water:",
        "{docid: 7, hitcount: 1}",
        "{docid: 8, hitcount: 1}",
      }),
      "rock:",
    };
    TestFunctionality(docs, queries, expected);
}

void TestHitcount() {
    const vector<string> docs = {
      "the river goes through the entire city there is a house near it",
      "the wall",
      "walle",
      "is is is is",
    };
    const vector<string> queries = { "the", "wall", "all", "is", "the is" };
    const vector<string> expected = {
      Join(' ', vector{
        "the:",
        "{docid: 0, hitcount: 2}",
        "{docid: 1, hitcount: 1}",
      }),
      "wall: {docid: 1, hitcount: 1}",
      "all:",
      Join(' ', vector{
        "is:",
        "{docid: 3, hitcount: 4}",
        "{docid: 0, hitcount: 1}",
      }),
      Join(' ', vector{
        "the is:",
        "{docid: 3, hitcount: 4}",
        "{docid: 0, hitcount: 3}",
        "{docid: 1, hitcount: 1}",
      }),
    };
    TestFunctionality(docs, queries, expected);
}

void TestRanking() {
    const vector<string> docs = {
      "london is the capital of great britain",
      "paris is the capital of france",
      "berlin is the capital of germany",
      "rome is the capital of italy",
      "madrid is the capital of spain",
      "lisboa is the capital of portugal",
      "bern is the capital of switzerland",
      "moscow is the capital of russia",
      "kiev is the capital of ukraine",
      "minsk is the capital of belarus",
      "astana is the capital of kazakhstan",
      "beijing is the capital of china",
      "tokyo is the capital of japan",
      "bangkok is the capital of thailand",
      "welcome to moscow the capital of russia the third rome",
      "amsterdam is the capital of netherlands",
      "helsinki is the capital of finland",
      "oslo is the capital of norway",
      "stockgolm is the capital of sweden",
      "riga is the capital of latvia",
      "tallin is the capital of estonia",
      "warsaw is the capital of poland",
    };

    const vector<string> queries = { "moscow is the capital of russia" };
    const vector<string> expected = {
      Join(' ', vector{
        "moscow is the capital of russia:",
        "{docid: 7, hitcount: 6}",
        "{docid: 14, hitcount: 6}",
        "{docid: 0, hitcount: 4}",
        "{docid: 1, hitcount: 4}",
        "{docid: 2, hitcount: 4}",
      })
    };
    TestFunctionality(docs, queries, expected);
}

void TestBasicSearch() {
    const vector<string> docs = {
      "we are ready to go",
      "come on everybody shake you hands",
      "i love this game",
      "just like exception safety is not about writing try catch everywhere in your code move semantics are not about typing double ampersand everywhere in your code",
      "daddy daddy daddy dad dad dad",
      "tell me the meaning of being lonely",
      "just keep track of it",
      "how hard could it be",
      "it is going to be legen wait for it dary legendary",
      "we dont need no education"
    };

    const vector<string> queries = {
      "we need some help",
      "it",
      "i love this game",
      "tell me why",
      "dislike",
      "about"
    };

    const vector<string> expected = {
      Join(' ', vector{
        "we need some help:",
        "{docid: 9, hitcount: 2}",
        "{docid: 0, hitcount: 1}"
      }),
      Join(' ', vector{
        "it:",
        "{docid: 8, hitcount: 2}",
        "{docid: 6, hitcount: 1}",
        "{docid: 7, hitcount: 1}",
      }),
      "i love this game: {docid: 2, hitcount: 4}",
      "tell me why: {docid: 5, hitcount: 2}",
      "dislike:",
      "about: {docid: 3, hitcount: 2}",
    };
    TestFunctionality(docs, queries, expected);
}

inline void TestAll() {
    TestRunner tr;

#ifdef MY_TEST

    RUN_TEST(tr, TestBasic);

#endif

#ifdef BIG_TEST

    BigTest();

#endif

#ifdef STD_TESTS
    RUN_TEST(tr, TestSerpFormat);
    RUN_TEST(tr, TestTop5);
    RUN_TEST(tr, TestHitcount);
    RUN_TEST(tr, TestRanking);
    RUN_TEST(tr, TestBasicSearch);
#endif

#ifdef DURATION_TEST
    const int count = 10000;
    {
        LOG_DURATION("TOTAL");
        {
            LOG_DURATION("TestSerpFormat");
            for (int i = 0; i < count; ++i) { TestSerpFormat(); }
        }
        {
            LOG_DURATION("TestTop5");
            for (int i = 0; i < count; ++i) { TestTop5(); }
        }
        {
            LOG_DURATION("TestHitcount");
            for (int i = 0; i < count; ++i) { TestHitcount(); }
        }
        {
            LOG_DURATION("TestRanking");
            for (int i = 0; i < count; ++i) { TestRanking(); }
        }
        {
            LOG_DURATION("TestBasicSearch");
            for (int i = 0; i < count; ++i) { TestBasicSearch(); }
}
}

#endif
}