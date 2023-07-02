#include "stats.h"
#include <vector>
#include <string>
#include <algorithm>

Stats::Stats() {
    for (size_t i = 0; i < methodsVector.size(); ++i) {
        methods[string_view(methodsVector[i])] = 0;
    }
    for (size_t i = 0; i < urisVector.size(); ++i) {
        uris[string_view(urisVector[i])] = 0;
    }
}

void Stats::AddMethod(string_view method) {
    if (find(methodsVector.begin(), methodsVector.end(), method) == methodsVector.end()) {
        methods["UNKNOWN"] += 1;
    } else {
        methods[method] += 1;
    }
}

void Stats::AddUri(string_view uri) {
    if (find(urisVector.begin(), urisVector.end(), uri) == urisVector.end()) {
        uris["unknown"] += 1;
    } else {
        uris[uri] += 1;
    }
}

const Stats::stats_& Stats::GetMethodStats() const {
    return methods;
}

const Stats::stats_& Stats::GetUriStats() const {
    return uris;
}

HttpRequest ParseRequest(string_view line) {
    HttpRequest result;

    while (line[0] == ' ') {
        line.remove_prefix(1);
    }
    size_t space = line.find(' ');
    result.method = line.substr(0, space);
    if (space != line.npos) line.remove_prefix(space + 1);

    space = line.find(' ');
    result.uri = line.substr(0, space);
    if (space != line.npos) line.remove_prefix(space + 1);
    result.protocol = line;

    return result;
}