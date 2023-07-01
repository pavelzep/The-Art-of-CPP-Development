#include "stats.h"
// #include <sstream>


vector<string> methodsVector = { "GET", "PUT", "POST", "DELETE", "UNKNOWN" };

void Stats::AddMethod(string_view method) {
    methods[method] += 1;
}

void Stats::AddUri(string_view uri) {
    uris[uri] += 1;
}

const Stats::stats_& Stats::GetMethodStats() const {
    return methods;
}

const Stats::stats_& Stats::GetUriStats() const {
    return uris;
}

HttpRequest ParseRequest(string_view line) {
    HttpRequest result;
    // stringstream in(line);

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

    // while (true) {
    //     size_t space = str.find(' ');
    //     result.push_back(str.substr(0, space));
    //     if (space == str.npos) {
    //         break;
    //     } else {
    //         str.remove_prefix(space + 1);
    //     }
    // }
    // return


    return result;
}
