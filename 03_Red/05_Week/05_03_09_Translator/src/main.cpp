#include "test_runner.h"
#include "translator.h"

using namespace std;

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
    ASSERT_EQUAL(translator.TranslateBackward("three"), "one");
    ASSERT_EQUAL(translator.TranslateBackward("two"), "one");
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestSimple);
    RUN_TEST(tr, TestSimple2);
    return 0;
}