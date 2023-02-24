#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
    os << "{";
    bool first = true;
    for (const auto& x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
    os << "{";
    bool first = true;
    for (const auto& x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
    os << "{";
    bool first = true;
    for (const auto& kv : m) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << kv.first << ": " << kv.second;
    }
    return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
    if (t != u) {
        ostringstream os;
        os << "Assertion failed: " << t << " != " << u;
        if (!hint.empty()) {
            os << " hint: " << hint;
        }
        throw runtime_error(os.str());
    }
}

void Assert(bool b, const string& hint) {
    AssertEqual(b, true, hint);
}

class TestRunner {
public:
    template <class TestFunc>
    void RunTest(TestFunc func, const string& test_name) {
        try {
            func();
            cerr << test_name << " OK" << endl;
        }
        catch (exception& e) {
            ++fail_count;
            cerr << test_name << " fail: " << e.what() << endl;
        }
        catch (...) {
            ++fail_count;
            cerr << "Unknown exception caught" << endl;
        }
    }

    ~TestRunner() {
        if (fail_count > 0) {
            cerr << fail_count << " unit tests failed. Terminate" << endl;
            exit(1);
        }
    }

private:
    int fail_count = 0;
};

// bool IsPalindrom(const string& str) {
//     bool flag = 1;
//     int strSize = str.size();
//     for (int i = 0; i < strSize / 2; ++i) {
//         if (str[i] != str[strSize - 1 - i]) {
//             flag = 0;
//             break;
//         }
//     }
//     return flag;
// }

void test0() {
    string  str = " ";
    AssertEqual(true, IsPalindrom(str));
}

void test01() {
    string  str = "qw";
    AssertEqual(false, IsPalindrom(str));
}

void test02() {
    string  str = "qww";
    AssertEqual(false, IsPalindrom(str));
}

void test03() {
    string  str = "qqw";
    AssertEqual(false, IsPalindrom(str));
}

void test1() {
    string  str = "";
    AssertEqual(true, IsPalindrom(str));
}

void test2() {
    string  str = "q";
    AssertEqual(true, IsPalindrom(str));
}

void test3() {
    string  str = "qweewq";
    AssertEqual(true, IsPalindrom(str));
}

void test4() {
    string  str = "q weew q";
    AssertEqual(true, IsPalindrom(str));
}

void test5() {
    string  str = "q we ew q";
    AssertEqual(true, IsPalindrom(str));
}

void test6() {
    string  str = "qwe ew q";
    AssertEqual(false, IsPalindrom(str));
}

void test7() {
    string  str = "q we w q";
    AssertEqual(false, IsPalindrom(str));
}
void test8() {
    string  str = "q we w q ";
    AssertEqual(false, IsPalindrom(str));
}


void TestAll() {
    TestRunner runner;

    runner.RunTest(test0, "test0");
    runner.RunTest(test01, "test01");
    runner.RunTest(test02, "test02");
    runner.RunTest(test03, "test03");
    runner.RunTest(test1, "test1");
    runner.RunTest(test2, "test2");
    runner.RunTest(test3, "test3");
    runner.RunTest(test4, "test4");
    runner.RunTest(test5, "test5");
    runner.RunTest(test6, "test6");
    runner.RunTest(test7, "test7");
    runner.RunTest(test8, "test8");

}


int main() {
    TestAll();
    return 0;
}
