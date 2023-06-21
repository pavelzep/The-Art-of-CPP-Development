#include "test_runner.h"
#include <string>
#include <vector>

using namespace std;

class Translator {
public:
    void Add(string_view source, string_view target) {

        set<string>::iterator s_it = store_s.emplace(source).first;
        set<string>::iterator t_it = store_t.emplace(target).first;

        store_vs[*s_it] = *t_it;
        store_vt[*t_it] = *s_it;
    }

    string_view TranslateForward(string_view source) const {
        if (!store_s.count(string(source))) {
            return "";
        }
        return store_vs.at(source);
    }
    string_view TranslateBackward(string_view target) const {
        if (!store_t.count(string(target))) {
            return "";
        }
        return  store_vt.at(target);
    }

private:
    set<string> store_s, store_t;
    map<string_view, string_view> store_vs, store_vt;

};

void TestSimple() {
    Translator translator;
    translator.Add(string("okno"), string("window"));
    translator.Add(string("stol"), string("table"));

    ASSERT_EQUAL(translator.TranslateForward("okno"), "window");
    ASSERT_EQUAL(translator.TranslateBackward("table"), "stol");
    ASSERT_EQUAL(translator.TranslateBackward("stol"), "");
}

void TestSimple2() {
    Translator translator;
    translator.Add(string("one"), string("two"));
    translator.Add(string("one"), string("three"));
    ASSERT_EQUAL(translator.TranslateForward("one"), "three");
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestSimple);
    RUN_TEST(tr, TestSimple2);
    return 0;
}