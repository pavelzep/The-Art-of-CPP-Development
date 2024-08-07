#include "global.h"

#ifdef TEST
    #include "test_runner.h"
#endif


#ifdef TEST

    #include <vector>
    #include <string>
    #include <iostream>
    #include <sstream>

    vector<string> ReadDomains(istream& in_stream , bool isNeedSort , bool isNeedThinOut );
    void printResult(const vector<bool>& result, ostream& out_stream ) ;
    vector<bool> checkDomains(const vector<string>& banned_domains, const vector<string>& domains_to_check) ;
#endif


#ifdef TEST
    void test_all();
    void Test0();
    void Test1();
    void Test2();
    void Test3();
    void Test4();
#endif

#ifdef TEST
    void test_all() {
        TestRunner tr;
        RUN_TEST(tr, Test0);
        RUN_TEST(tr, Test1);
        RUN_TEST(tr, Test2);
        // RUN_TEST(tr, Test3);
        // RUN_TEST(tr, Test4);
    }
    void Test0() {
        std::istringstream banned_domains_ss(
            "4\n"       \
            "ya.ru\n"   \
            "maps.me\n" \
            "m.ya.ru\n" \
            "com\n"
        );

        std::istringstream domains_to_check_ss(
            "7\n"               \
            "ya.ru\n"           \
            "ya.com\n"          \
            "m.maps.me\n"       \
            "moscow.m.ya.ru\n"  \
            "maps.com\n"        \
            "maps.ru\n"         \
            "ya.ya\n"
        );

        const vector<string> banned_domains = ReadDomains(banned_domains_ss, true, true);
        const vector<string> domains_to_check = ReadDomains(domains_to_check_ss, false, false);

        ostringstream out;
        printResult(checkDomains(banned_domains, domains_to_check), out);
        string out_str = out.str();
        string right_res(
            "Bad\n"     \
            "Bad\n"     \
            "Bad\n"     \
            "Bad\n"     \
            "Bad\n"     \
            "Good\n"    \
            "Good\n"
        );

        ASSERT_EQUAL(out_str, right_res);

    }
    void Test1() {
        std::istringstream banned_domains_ss(
            "11\n"       \
            "ya.ru\n"   \
            "maps.me\n" \
            "m.ya.ru\n" \
            "a.ya.ru\n" \
            "b.ya.ru\n" \
            "a.c.ya.ru\n" \
            "b.c.ya.ru\n" \
            "b.a.ya.rz\n" \
            "a.b.ya.rz\n" \
            "b.b.ya.rz\n" \
            "com\n"
        );

        std::istringstream domains_to_check_ss(
            "7\n"               \
            "ya.ru\n"           \
            "ya.com\n"          \
            "m.maps.me\n"       \
            "moscow.m.ya.ru\n"  \
            "maps.com\n"        \
            "maps.ru\n"         \
            "ya.ya\n"
        );

        const vector<string> banned_domains = ReadDomains(banned_domains_ss, true, true);
        const vector<string> domains_to_check = ReadDomains(domains_to_check_ss, false, false);


        ostringstream out;
        printResult(checkDomains(banned_domains, domains_to_check), out);
        string right_res(
            "Bad\n"     \
            "Bad\n"     \
            "Bad\n"     \
            "Bad\n"     \
            "Bad\n"     \
            "Good\n"    \
            "Good\n"
        );
        ASSERT_EQUAL(out.str(), right_res);

    }
    void Test2() {
        std::istringstream banned_domains_ss(
            "1\n"       \
            "com\n"
        );

        std::istringstream domains_to_check_ss(
            "2\n"               \
            "ya.com\n"          \
            "rrr.scom\n"       \
        );

        const vector<string> banned_domains = ReadDomains(banned_domains_ss, true, true);
        const vector<string> domains_to_check = ReadDomains(domains_to_check_ss, false, false);

        ostringstream out;
        printResult(checkDomains(banned_domains, domains_to_check), out);
        string right_res(
            "Bad\n"     \
            "Good\n"    \
        );
        ASSERT_EQUAL(out.str(), right_res);
    }
    void Test3() {


    }
    void Test4() {


}
#endif