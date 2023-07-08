#include "test_runner.h"

#include <algorithm>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <utility>

using namespace std;

// Объявляем Group<String> для произвольного типа String
// синонимом vector<String>.
// Благодаря этому в качестве возвращаемого значения
// функции можно указать не малопонятный вектор векторов,
// а вектор групп — vector<Group<String>>.
template <typename String>
using Group = vector<String>;

// Ещё один шаблонный синоним типа
// позволяет вместо громоздкого typename String::value_type
// использовать Char<String>
template <typename String>
using Char = typename String::value_type;

template <typename String>
vector<Group<String>> GroupHeavyStrings(vector<String> strings) {
    // Напишите реализацию функции,
    // использовав не более 1 копирования каждого символа

    set<typename String::value_type> key;

    map< set <Char<String>>, Group<String>> mapStrings;
    for (const String& item : strings) {
        set<Char<String>> key(make_move_iterator(begin(item)), make_move_iterator(end(item)));
        mapStrings[move(key)].push_back(move(item));
    }

    vector<Group<String>> result;
    for (const auto& item : mapStrings) {
        result.push_back(move(item.second));
    }

    return result;
}


void TestGroupingABC() {
    vector<string> strings = { "caab", "abc", "cccc", "bacc", "c" };
    auto groups = GroupHeavyStrings(strings);
    ASSERT_EQUAL(groups.size(), 2);
    sort(begin(groups), end(groups));  // Порядок групп не имеет значения
    ASSERT_EQUAL(groups[0], vector<string>({ "caab", "abc", "bacc" }));
    ASSERT_EQUAL(groups[1], vector<string>({ "cccc", "c" }));
}

void TestGroupingReal() {
    vector<string> strings = { "law", "port", "top", "laptop", "pot", "paloalto", "wall", "awl" };
    auto groups = GroupHeavyStrings(strings);
    ASSERT_EQUAL(groups.size(), 4);
    sort(begin(groups), end(groups));  // Порядок групп не имеет значения
    ASSERT_EQUAL(groups[0], vector<string>({ "laptop", "paloalto" }));
    ASSERT_EQUAL(groups[1], vector<string>({ "law", "wall", "awl" }));
    ASSERT_EQUAL(groups[2], vector<string>({ "port" }));
    ASSERT_EQUAL(groups[3], vector<string>({ "top", "pot" }));
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestGroupingABC);
    RUN_TEST(tr, TestGroupingReal);
    return 0;
}
