#include <iostream>
#include <list>
#include <map>

using namespace std;

class Athlets {
private:
    map<int, list<int>::iterator> its;
    list<int> athlets;

public:
    void AddAthlet(int ath, int pos) {
        if (!its.count(pos)) {
            its[ath] = athlets.insert(athlets.end(), ath);
            return;
        }
        its[ath] = athlets.insert(its[pos], ath);
    }

    void Print() {
        for (const auto& item : athlets) {
            cout << item << ' ';
        }
    }
};

int main() {
    int q;
    cin >> q;

    int ath, pos;

    Athlets athlets;
    while (q) {
        cin >> ath >> pos;
        athlets.AddAthlet(ath, pos);
        --q;
    }

    athlets.Print();
    return 0;
}