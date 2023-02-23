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

class Rational {
public:
    Rational() {
        p = 0;
        q = 1;
    }
    Rational(int numerator, int denominator) {
        p = numerator;
        q = denominator;
        int gcd = GCD(p, q);
        p /= gcd;
        q /= gcd;
        if (q < 0) {
            p = -p;
            q = -q;
        }
    }
    int Numerator() const {
        return p;
    }
    int Denominator() const {
        return q;
    }
private:
    int p;
    int q;
    int GCD(int a, int b) {
        return b ? GCD(b, a % b) : a;
    }
};


void test1() {
    Rational r;
    AssertEqual(r.Numerator(), 0);
    AssertEqual(r.Denominator(), 1);
}

void test2() {
    {
        Rational r(2, 3);
        AssertEqual(r.Numerator(), 2);
        AssertEqual(r.Denominator(), 3);
    }
    {
        Rational r(11, 17);
        AssertEqual(r.Numerator(), 11);
        AssertEqual(r.Denominator(), 17);
    }

}

void test3() {
    {
        Rational r(4, 6);
        AssertEqual(r.Numerator(), 2);
        AssertEqual(r.Denominator(), 3);
    }
    {
        Rational r(9999999, 3333333);
        AssertEqual(r.Numerator(), 3);
        AssertEqual(r.Denominator(), 1);
    }
    {
        Rational r(17, 51);
        AssertEqual(r.Numerator(), 1);
        AssertEqual(r.Denominator(), 3);
    }
}

void test4() {
    {
        Rational r(-2, 3);
        AssertEqual(r.Numerator(), -2);
        AssertEqual(r.Denominator(), 3);
    }
}

void test5() {
    {
        Rational r(2, -3);
        AssertEqual(r.Numerator(), -2);
        AssertEqual(r.Denominator(), 3);
    }
}

void test6() {
    {
        Rational r(0, 4);
        AssertEqual(r.Numerator(), 0);
        AssertEqual(r.Denominator(), 1);
    }
}

void test7() {
    {
        Rational r(-2, -3);
        AssertEqual(r.Numerator(), 2);
        AssertEqual(r.Denominator(), 3);
    }
}

void TestAll() {
    TestRunner runner;
    runner.RunTest(test1, "test1");
    runner.RunTest(test2, "test2");
    runner.RunTest(test3, "test3");
    runner.RunTest(test4, "test4");
    runner.RunTest(test5, "test5");
    runner.RunTest(test6, "test6");
    runner.RunTest(test7, "test7");
}

int main() {
    TestAll();

    return 0;
}
