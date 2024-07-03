#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include "test_runner.h"

#define TEST

#ifdef TEST
void test_all();
void Test1();
void Test2();
void Test3();
void Test4();
#endif

using namespace std;

bool isSubDomain(const string& check, const string& b_domain) {
    if (check.find(b_domain) == 0) {
        auto bad_size = b_domain.size();
        auto check_size = check.size();
        if (bad_size >= check_size)
            return 1;
        else if (check.at(bad_size) == '.')
            return 1;
    }
    return 0;
}

bool isSubDomain(const string& check, const vector<string>& banned_domains) {
    auto it = upper_bound(banned_domains.begin(), banned_domains.end(), check);
    return 0;
}

vector<string> ReadDomains(istream& in_stream = cin, bool isNeedSort = false, bool isNeedThinOut = false) {
    size_t count;
    in_stream >> count;
    in_stream.ignore();
    vector<string> domains;

    domains.reserve(count);

    for (size_t i = 0; i < count; ++i) {
        string domain;
        getline(in_stream, domain);
        reverse(domain.begin(), domain.end());
        domains.push_back(move(domain));
    }
    if (isNeedSort)
        sort(begin(domains), end(domains));
    if (isNeedThinOut) {
        size_t insert_pos = 0;
        for (string& domain : domains) {
            if (insert_pos == 0 || !isSubDomain(domain, domains[insert_pos - 1])) {
                swap(domains[insert_pos++], domain);
            }
        }
        domains.resize(insert_pos);
    }
    return domains;

}




void printResult(const vector<bool>& result, ostream& out_stream = cout) {
    for (const auto& res : result) {
        res ? out_stream << "Bad" : out_stream << "Good";
        out_stream << '\n';
    }
}

vector<bool> checkDomains(const vector<string>& banned_domains, const vector<string>& domains_to_check) {
    vector<bool> results;
    results.reserve(domains_to_check.size());

    for (const auto& domain : domains_to_check) {
        results.push_back(isSubDomain(domain, banned_domains));
    }
    return results;
}

int main() {

#ifdef TEST
    test_all();
#else
    const vector<string> banned_domains = ReadDomains();
    const vector<string> domains_to_check = ReadDomains();
    printResult(checkDomains(banned_domains, domains_to_check));
#endif
    return 0;
}
#ifdef TEST
void test_all() {
    TestRunner tr;
    RUN_TEST(tr, Test1);
    // RUN_TEST(tr, Test2);
    // RUN_TEST(tr, Test3);
    // RUN_TEST(tr, Test4);
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
    const vector<string> domains_to_check = ReadDomains(domains_to_check_ss);


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

    const vector<string> banned_domains = ReadDomains(banned_domains_ss);
    const vector<string> domains_to_check = ReadDomains(domains_to_check_ss);

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