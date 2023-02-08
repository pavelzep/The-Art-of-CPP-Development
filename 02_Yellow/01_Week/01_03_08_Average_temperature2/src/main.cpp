#include <iostream>
#include <vector>

using namespace std;

int main() {
    uint32_t number;
    cin >> number;

    vector<int64_t> temp(number);
    int64_t sum = 0;
    for (auto& t : temp) {
        cin >> t;
        sum += t;
    }

    int64_t avr = sum / number;
    //cout << avr << endl;
    uint32_t count = 0;

    vector<uint32_t> above_average_numb;
    for (uint32_t i = 0; i < number;++i) {
        if (temp.at(i) > avr) {
            count++;
            above_average_numb.push_back(i);
        }
    }

    cout << count << endl;

    for (uint32_t i = 0; i < count;++i) {
        cout << above_average_numb[i];
        if(i!=count-1) cout << " ";
    }

    return 0;
}
