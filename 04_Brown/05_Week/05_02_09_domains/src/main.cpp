#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

// #include "global.h"

#ifdef TEST
extern void test_all();
// #include "tests.h"
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

    auto up = upper_bound(banned_domains.begin(), banned_domains.end(), check);
    if(up==banned_domains.begin()) return 0;
    auto t = *prev(up);
    auto res = isSubDomain(check, t);
    return res;
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
    const vector<string> banned_domains = ReadDomains(cin, true, true);
    const vector<string> domains_to_check = ReadDomains();
    printResult(checkDomains(banned_domains, domains_to_check));
#endif
    return 0;
}
