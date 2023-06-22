#pragma once
#include <string>
#include <map>
#include <set>

using namespace std;

class Translator {
public:
    void Add(string_view source, string_view target) {

        auto s_it = store.emplace(source).first;
        auto t_it = store.emplace(target).first;

        store_vs[*s_it] = *t_it;
        store_vt[*t_it] = *s_it;
    }

    string_view TranslateForward(string_view source) const {
        return Translate(source, store_vs);
    }

    string_view TranslateBackward(string_view target) const {
        return Translate(target, store_vt);
    }

private:
    set<string> store;
    map<string_view, string_view> store_vs, store_vt;

    string_view Translate(string_view _word, const map<string_view, string_view>& _map) const {
        if (!_map.count(_word)) {
            return {};
        };
        return  _map.at(_word);
    }
};