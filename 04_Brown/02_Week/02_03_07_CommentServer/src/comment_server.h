#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <utility>
#include <map>
#include <optional>
#include <unordered_set>


using namespace std;

pair<string, string> SplitBy(const string& what, const string& by);

struct HttpRequest {
   
    std::string method, path, body;
    std::map<std::string, std::string> get_params;
};

struct LastCommentInfo {
    size_t user_id, consecutive_count;
};

struct HttpHeader {
    std::string name, value;
};

struct ParsedResponse {
    int code;
    std::vector<HttpHeader> headers;
    std::string content;
};

class CommentServer {

private:

    std::vector<std::vector<std::string>> comments_;
    std::optional<LastCommentInfo> last_comment;
    std::unordered_set<size_t> banned_users;

public:
    void ServeRequest(const HttpRequest& req, std::ostream& os);
};


ostream& operator<<(ostream& output, const HttpHeader& h);

bool operator==(const HttpHeader& lhs, const HttpHeader& rhs) ;

istream& operator >>(istream& input, ParsedResponse& r);
