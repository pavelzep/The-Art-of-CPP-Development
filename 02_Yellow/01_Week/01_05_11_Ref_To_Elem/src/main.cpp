#include <string>
#include <iostream>

#include <map> 

using namespace std;

template <typename key, typename value>
value& GetRefStrict(map <key, value>& m);

template <typename key, typename value>
value& GetRefStrict(map <key, value>& m, key k) {
    if (m.count(k) == 0) {
        throw runtime_error("");
    } else return m[k];
}

int main() {

    map<int, string> m = { {0, "value"} };
    string& item = GetRefStrict(m, 0);
    item = "newvalue";
    cout << m[0] << endl;

    map<string, string> sd = { {"str", "value"} };
    cout << sd["str"] << endl;

    // cout << GetRefStrict(m, 3) << endl;
    return 0;
}