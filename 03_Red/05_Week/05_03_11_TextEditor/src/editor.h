#pragma once

#include <list>
#include <string>
#include <iterator>


using namespace std;

class Editor {
public:

    Editor() {
        pos = data.end();
    }

    void Left() {
        if (pos != data.begin())
            pos = prev(pos);
    }

    void Right() {
        if (pos != data.end())
            pos = next(pos);
    }

    void Insert(char token) {
        pos = data.insert(pos, token);
        pos = next(pos);
    }

    void Cut(size_t tokens = 1) {
        buff.clear();
        auto from = pos;
        auto to = pos;

        // advance(to, tokens);  
        while (tokens&&(to!=data.end())) {
            to = next(to);
            --tokens;
        }

        pos = to;
        buff.insert(buff.begin(), from, to);
        data.erase(from, to);
    }

    void Copy(size_t tokens = 1) {
        buff.clear();
        auto from = pos;
        auto to = pos;

        // advance(to, tokens);  
        while (tokens&&(to!=data.end())) {
            to = next(to);
            --tokens;
        }

        pos = to;
        buff.insert(buff.begin(), from, to);

    }

    void Paste() {
        data.insert(pos, buff.begin(), buff.end());
        // advance(pos, buff.size());
    }

    string GetText() const {
        return string(data.begin(), data.end());
    }

private:
    list<char> data;
    list<char>::iterator pos;
    list<char> buff;
};