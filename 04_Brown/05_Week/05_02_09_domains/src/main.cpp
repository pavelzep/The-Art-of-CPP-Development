#include <algorithm>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include <sstream>

using namespace std;


bool IsSubdomain(string_view subdomain, string_view domain) {
    auto i = subdomain.size() - 1;
    auto j = domain.size() - 1;
    while (i >= 0 && j >= 0) {
        if (subdomain[i--] != domain[j--]) {
            return false;
        }
    }
    return (i < 0 && domain[j] == '.')
        || (j < 0 && subdomain[i] == '.');
}


vector<string> ReadDomains(istream& in_stream = cin) {
    size_t count;
    in_stream >> count;
    in_stream.ignore();
    vector<string> domains;
    for (size_t i = 0; i < count; ++i) {
        string domain;
        getline(in_stream, domain);
        domains.push_back(domain);
    }
    return domains;
}


int main() {

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

    // std::string str1 = banned_domains_ss.str();
    // std::string str2 = domains_to_check_ss.str();

    vector<string> banned_domains = ReadDomains(banned_domains_ss);
    const vector<string> domains_to_check = ReadDomains(domains_to_check_ss);

    for (string& domain : banned_domains) {
        reverse(begin(domain), end(domain));
    }
    sort(begin(banned_domains), end(banned_domains));

    //   size_t insert_pos = 0;
    //   for (string& domain : banned_domains) {
    //     if (insert_pos == 0 || !IsSubdomain(domain, banned_domains[insert_pos - 1])) {
    //       swap(banned_domains[insert_pos++], domain);
    //     }
    //   }
    //   banned_domains.resize(insert_pos);

    //   for (const string_view domain : domains_to_check) {
    //     if (const auto it = upper_bound(begin(banned_domains), end(banned_domains), domain);
    //         it != begin(banned_domains) && IsSubdomain(domain, *prev(it))) {
    //       cout << "Good" << endl;
    //     } else {
    //       cout << "Bad" << endl;
    //     }
    //   }
    return 0;
}
