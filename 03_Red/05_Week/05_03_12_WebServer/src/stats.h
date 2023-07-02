#pragma once

#include "http_request.h"
#include <string_view>
#include <map>
#include <vector>
#include <string>

using namespace std;

class Stats {
public:
    using stats_ = map<string_view, int>;
    Stats();

    void AddMethod(string_view method);
    void AddUri(string_view uri);

    const Stats::stats_& GetMethodStats() const;
    const Stats::stats_& GetUriStats() const;

private:
    Stats::stats_ methods;
    Stats::stats_ uris;

    vector<string> methodsVector{ "GET", "PUT", "POST", "DELETE", "UNKNOWN" };
    vector<string> urisVector{ "/", "/order", "/product", "/basket", "/help","unknown" };

};

HttpRequest ParseRequest(string_view line);