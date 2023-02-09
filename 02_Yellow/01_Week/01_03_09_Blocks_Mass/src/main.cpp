#include <iostream>


using namespace std;
int main() {
    int N;          //  <100'000
    int R;           //  <100
    int W, H, D;    //  <10'000

    cin >> N >> R;

    uint64_t rez = 0 ;


    while (N)

    {
        cin >> W >> H >> D;
        rez += (
            static_cast<uint64_t>(W) *
            static_cast<uint64_t>(H) *
            static_cast<uint64_t>(D)
            );
        N--;
    }

    cout << rez*R;


    return 0;
}