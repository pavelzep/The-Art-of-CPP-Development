#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

enum class Lang {
    DE, FR, IT
};

struct Region {
    string std_name;
    string parent_std_name;
    map<Lang, string> names;
    int64_t population;
};

int FindMaxRepetitionCount(const vector<Region>& regions) {
   // if (regions.size() < 2) return regions.size();

    map <tuple<const string&, const string&, const map<Lang, string>&, const int64_t&>, int> unics;
    int rez = 0;

    for (const auto& item : regions) {
        auto t = tie(item.std_name, item.parent_std_name, item.names, item.population);
        unics[t] = (unics.count(t) ? unics[t] + 1 : 1);
        rez = unics[t]>rez? unics[t] : rez;
    }
    return rez;

};

int FindMaxRepetitionCount3(const vector<Region>& regions) {
    auto temp = regions;
    int rez = 0;
    int base_size = temp.size();
    if (base_size > 1) {
        int count = 1;
        for (int i = 0; i < base_size; i++) {

            auto t1 = tie(temp.at(i).std_name, temp.at(i).parent_std_name, temp.at(i).names, temp.at(i).population);
            count = 1;
            for (int j = i + 1; j < base_size;j++) {
                auto t2 = tie(temp.at(j).std_name, temp.at(j).parent_std_name, temp.at(j).names, temp.at(j).population);
                if (t1 == t2) {
                    count++;
                    temp.erase(temp.begin() + j);
                    base_size--;
                    j--;
                }
                if (count > rez) rez = count;
            }
        }
    } else {
        return base_size;
    }
    return rez;
};

int FindMaxRepetitionCount2(const vector<Region>& regions) {
    int rez = 0;
    int base_size = regions.size();
    if (base_size > 1) {
        int count = 1;
        for (int i = 0; i < base_size; i++) {

            auto t1 = tie(regions.at(i).std_name, regions.at(i).parent_std_name, regions.at(i).names, regions.at(i).population);
            count = 1;
            for (int j = i + 1; j < base_size;j++) {
                auto t2 = tie(regions.at(j).std_name, regions.at(j).parent_std_name, regions.at(j).names, regions.at(j).population);
                if (t1 == t2) {
                    count++;
                }
                if (count > rez) rez = count;
            }
        }
    } else {
        return base_size;
    }
    return rez;
};

int main() {

    cout << FindMaxRepetitionCount({}) << endl;

    cout << FindMaxRepetitionCount({
    {
        "Moscow",
        "Russia",
        {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
        89
    } }) << endl;

    cout << FindMaxRepetitionCount({
     {
         "Moscow",
         "Russia",
         {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
         89
     }, {
         "Russia",
         "Eurasia",
         {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
         89
     }, {
         "Moscow",
         "Russia",
         {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
         89
     }, {
         "Moscow",
         "Russia",
         {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
         89
     }, {
         "Russia",
         "Eurasia",
         {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
         89
     },
        }) << endl;

    cout << FindMaxRepetitionCount({
        {
            "Moscow",
            "Russia",
            {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
            89
        }, {
            "Russia",
            "Eurasia",
            {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
            89
        }, {
            "Moscow",
            "Russia",
            {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou deux"}, {Lang::IT, "Mosca"}},
            89
        }, {
            "Moscow",
            "Toulouse",
            {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
            89
        }, {
            "Moscow",
            "Russia",
            {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
            31
        },
        }) << endl;

    return 0;
}