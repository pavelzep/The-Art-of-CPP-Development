#include <algorithm>
#include <string>
#include <vector>
#include <set>


using namespace std;

// class Learner2 {
// private:
//     vector<string> dict;

// public:
//     int Learn(const vector<string>& words) {
//         int newWords = 0;
//         for (const auto& word : words) {
//             if (find(dict.begin(), dict.end(), word) == dict.end()) {
//                 ++newWords;
//                 dict.push_back(word);
//             }
//         }
//         return newWords;
//     }

//     vector<string> KnownWords() {
//         sort(dict.begin(), dict.end());
//         dict.erase(unique(dict.begin(), dict.end()), dict.end());
//         return dict;
//     }
// };

class Learner {
private:
    set<string> dict;

public:
    int Learn(const vector<string>& words) {
        size_t old_size = dict.size();
        dict.insert(words.begin(), words.end());
        return dict.size() - old_size;
    }

    vector<string> KnownWords() {
        vector<string> result(dict.begin(), dict.end());
        return result;
    }
};
