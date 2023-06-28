#pragma once

#include <deque>
#include <string>
#include <iterator>

using namespace std;

class Editor {
public:

    Editor() {
        pos = data.end();
    }

    void Left() {
        pos = prev(pos);
    }

    void Right() {
        pos = next(pos);
    }

    void Insert(char token) {
        pos = data.insert(pos, token);

    }

    void Cut(size_t tokens = 1) {
        buff.clear();
        auto from = pos;
        advance(pos, tokens);
        buff.insert(buff.begin(), from, pos);
        data.erase(from, pos);
    }

    void Copy(size_t tokens = 1) {
        buff.clear();
        auto from = pos;
        advance(pos, tokens);
        buff.insert(buff.begin(), from, pos);

    }

    void Paste() {
        data.insert(pos, buff.begin(), buff.end());
    }

    string GetText() const {
        return string(data.begin(), data.end());
    }
private:

    deque<char> data;
    deque<char>::iterator pos;
    deque<char> buff;


};