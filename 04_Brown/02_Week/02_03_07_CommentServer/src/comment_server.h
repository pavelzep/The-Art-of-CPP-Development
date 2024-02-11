#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <utility>
#include <map>
#include <optional>
#include <unordered_set>

namespace Comment_Server {
    using namespace std;
    // using std::string;
    // using std::map;
    // using std::pair;
    // using std::vector;
    // using std::optional;
    // using std::istream;
    // using std::ostream;
    // using std::unordered_set;


    pair<string, string> SplitBy(const string& what, const string& by);

    struct HttpRequest {
        using string = string;

        string method, path, body;
        map<string, string> get_params;
    };

    struct LastCommentInfo {
        size_t user_id, consecutive_count;
    };

    struct HttpHeader {
        string name, value;
    };

    struct ParsedResponse {
        int code;
        vector<HttpHeader> headers;
        string content;
    };

    class CommentServer {

    private:

        vector<vector<string>> comments_;
        optional<LastCommentInfo> last_comment;
        unordered_set<size_t> banned_users;

    public:
        void ServeRequest(const HttpRequest& req, std::ostream& os);
        // HttpResponse ServeRequest(const HttpRequest& req);
    };

    ostream& operator<<(ostream& output, const HttpHeader& h);

    bool operator==(const HttpHeader& lhs, const HttpHeader& rhs);

    istream& operator >>(istream& input, ParsedResponse& r);
}