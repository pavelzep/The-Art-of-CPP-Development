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

/*
int GetDistinctRealRootCount(double a, double b, double c) {
    if (a) {
        double d = b * b - 4 * a * c;
        if (d == 0) {
            return 1;
        } else {
            if (d > 0) {
                return 2;
            } else {
                return 0;
            }
        }
    } else if (b) return 1;
    else return 0;
}
*/

void Test_If_A_zero_B_not_zero() {
    AssertEqual(GetDistinctRealRootCount(0, 1, 1), 1);
}

void Test_If_A_zero_B_zero() {
    AssertEqual(GetDistinctRealRootCount(0, 0, 1), 0);
}

void Test_If_B_zero_C_negative() {
    AssertEqual(GetDistinctRealRootCount(1, 0, -0.000'000'1), 2);
    AssertEqual(GetDistinctRealRootCount(1, 0, -1), 2);
    AssertEqual(GetDistinctRealRootCount(1, 0, -999), 2);
    AssertEqual(GetDistinctRealRootCount(1, 0, -999'999'999'999), 2);
    AssertEqual(GetDistinctRealRootCount(1, 0, -1'000'000'000'000), 2);
}

void Test_If_B_zero_C_positive() {
    AssertEqual(GetDistinctRealRootCount(1, 0, 1), 0);
    AssertEqual(GetDistinctRealRootCount(1, 0, 999), 0);
    AssertEqual(GetDistinctRealRootCount(1, 0, 0.000'001), 0);
    AssertEqual(GetDistinctRealRootCount(1, 0, 999'999'999'999), 0);
    AssertEqual(GetDistinctRealRootCount(1, 0, 1'000'000'000'000), 0);
}

void Test_If_B_zero_C_zero() {
    AssertEqual(GetDistinctRealRootCount(1, 0, 0), 1);
    AssertEqual(GetDistinctRealRootCount(-1, 0, 0), 1);
    AssertEqual(GetDistinctRealRootCount(999, 0, 0), 1);
    AssertEqual(GetDistinctRealRootCount(-999, 0, 0), 1);
    AssertEqual(GetDistinctRealRootCount(999'999'999'999, 0, 0), 1);
    AssertEqual(GetDistinctRealRootCount(-999'999'999'999, 0, 0), 1);
}


void Test_If_A_B_C_not_zero() {
  
    AssertEqual(GetDistinctRealRootCount(-2, -4, 10), 2);
    AssertEqual(GetDistinctRealRootCount(2, 4, -10), 2);
    AssertEqual(GetDistinctRealRootCount(-2, 4, -10), 0);
    AssertEqual(GetDistinctRealRootCount(-2, -4, -10), 0);
    AssertEqual(GetDistinctRealRootCount(2, -12, 18), 1);
    AssertEqual(GetDistinctRealRootCount(-2, +12, -18), 1);
}



void Test_All() {
    TestRunner runner;

    runner.RunTest(Test_If_A_zero_B_not_zero, "Test_If_A_zero_B_not_zero");
    runner.RunTest(Test_If_A_zero_B_zero, "Test_If_A_zero_B_zero");

    runner.RunTest(Test_If_B_zero_C_positive, "Test_If_B_zero_C_positive");
    runner.RunTest(Test_If_B_zero_C_negative, "Test_If_B_zero_C_negative");
    runner.RunTest(Test_If_B_zero_C_zero, "Test_If_B_zero_C_zero");

    runner.RunTest(Test_If_A_B_C_not_zero, "Test_If_A_B_C_not_zero");
}

int main() {
    Test_All();

    return 0;
}
