#include "comment_server.h"

    using std::string;
    using std::map;
    using std::pair;
    using std::vector;
    using std::optional;
    using std::istream;
    using std::ostream;
    using std::unordered_set;
    using std::istringstream;



pair<string, string> SplitBy(const string& what, const string& by) {
    size_t pos = what.find(by);
    if (by.size() < what.size() && pos < what.size() - by.size()) {
        return { what.substr(0, pos), what.substr(pos + by.size()) };
    } else {
        return { what, {} };
    }
}

template<typename T>
T FromString(const string& s) {
    T x;
    istringstream is(s);
    is >> x;
    return x;
}

pair<size_t, string> ParseIdAndContent(const string& body) {
    auto [id_string, content] = SplitBy(body, " ");
    return { FromString<size_t>(id_string), content };
}

void CommentServer::ServeRequest(const HttpRequest& req, ostream& os) {
    if (req.method == "POST") {
        if (req.path == "/add_user") {
            comments_.emplace_back();
            auto response = std::to_string(comments_.size() - 1);
            os << "HTTP/1.1 200 OK\n" << "Content-Length: " << response.size() << "\n" << "\n"
                << response;
        } else if (req.path == "/add_comment") {
            auto [user_id, comment] = ParseIdAndContent(req.body);

            if (!last_comment || last_comment->user_id != user_id) {
                last_comment = LastCommentInfo{ user_id, 1 };
            } else if (++last_comment->consecutive_count > 3) {
                banned_users.insert(user_id);
            }

            if (banned_users.count(user_id) == 0) {
                comments_[user_id].push_back(string(comment));
                os << "HTTP/1.1 200 OK\n\n";
            } else {
                os << "HTTP/1.1 302 Found\n\n"
                    "Location: /captcha\n"
                    "\n";
            }
        } else if (req.path == "/checkcaptcha") {
            if (auto [id, response] = ParseIdAndContent(req.body); response == "42") {
                banned_users.erase(id);
                if (last_comment && last_comment->user_id == id) {
                    last_comment.reset();
                }
                os << "HTTP/1.1 200 OK\n\n";
            }
        } else {
            os << "HTTP/1.1 404 Not found\n\n";
        }
    } else if (req.method == "GET") {
        if (req.path == "/user_comments") {
            auto user_id = FromString<size_t>(req.get_params.at("user_id"));
            string response;
            for (const string& c : comments_[user_id]) {
                response += c + '\n';
            }

            os << "HTTP/1.1 200 OK\n" << "Content-Length: " << response.size() << response;
        } else if (req.path == "/captcha") {
            os << "HTTP/1.1 200 OK\n" << "Content-Length: 80\n" << "\n"
                << "What's the answer for The Ultimate Question of Life, the Universe, and Everything?";
        } else {
            os << "HTTP/1.1 404 Not found\n\n";
        }
    }
}

ostream& operator<<(ostream& output, const HttpHeader& h) {
    return output << h.name << ": " << h.value;
}

bool operator==(const HttpHeader& lhs, const HttpHeader& rhs) {
    return lhs.name == rhs.name && lhs.value == rhs.value;
}

istream& operator >>(istream& input, ParsedResponse& r) {
    string line;
    getline(input, line);

    {
        istringstream code_input(line);
        string dummy;
        code_input >> dummy >> r.code;
    }

    size_t content_length = 0;

    r.headers.clear();
    while (getline(input, line) && !line.empty()) {
        if (auto [name, value] = SplitBy(line, ": "); name == "Content-Length") {
            istringstream length_input(value);
            length_input >> content_length;
        } else {
            r.headers.push_back({ std::move(name), std::move(value) });
        }
    }

    r.content.resize(content_length);
    input.read(r.content.data(), r.content.size());
    return input;
}

HttpResponse::HttpResponse(HttpCode code) {

}

HttpResponse ServeRequest(const HttpRequest& req) {
    static HttpResponse result = HttpResponse(HttpCode::NotFound);
    return result;
}

HttpResponse& HttpResponse::AddHeader(string name, string value) {
    return *this;
}

HttpResponse& HttpResponse::SetContent(string a_content) {
    return *this;
}

HttpResponse& HttpResponse::SetCode(HttpCode a_code) {
    return *this;
}

ostream& operator<<(ostream& output, const HttpResponse& resp) {
    return output;
}
