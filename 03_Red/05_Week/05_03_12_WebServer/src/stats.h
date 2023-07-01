#pragma once

#include "http_request.h"

#include <string_view>
#include <map>
#include <vector>

using namespace std;

enum class METHODS {
    GET,
    PUT,
    POST,
    DELETE,
    UNKNOWN,
    Last_
};

class Stats {
public:

    using stats_ = map<string_view, int>;

    void AddMethod(string_view method);
    void AddUri(string_view uri);

    const  stats_& GetMethodStats() const;
    const  stats_& GetUriStats() const;

private:
    stats_ methods;
    stats_ uris;
};

HttpRequest ParseRequest(string_view line);