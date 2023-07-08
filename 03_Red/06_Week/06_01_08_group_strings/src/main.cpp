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

    map< set <Char<String>>, Group<String>> mapStrings;
    for (const String& item : strings) {

        mapStrings[set<Char<String>>((begin(item)), (end(item)))].push_back(move(item));

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


struct MyChar {
    char value;
    // int count = 0;

    // MyChar(const MyChar& c) {
    //     value = c.value;
    //     ++count;
    // };

    // MyChar& operator=(const MyChar& c) {
    //     value = c.value;
    //     ++count;
    //     return *this;
    // };
    // MyChar(const MyChar&) = delete;
    // MyChar& operator=(const MyChar&) = delete;

    // MyChar(MyChar&&) = default;
    // MyChar& operator=(MyChar&&) = default;


};


bool operator < (const MyChar& lhs, const MyChar& rhs) {
    return lhs.value == rhs.value;
}

void TestVectorSymbols() {
    vector < vector<MyChar>> noncopyableChars = {
        {{'b'}, {'a'}, {'c'}, {'a'},{ 'd'}, {'e'}} ,
        {{'b'},{'b'},{'b'}, {'a'}, {'c'}, {'a'}, {'d'}, {'e'}, {'e'}, {'e'}},
        {{'z'},{'z'},{'z'}}
    };
    auto groups = GroupHeavyStrings(noncopyableChars);
    ASSERT_EQUAL(groups.size(), 2);
    sort(begin(groups), end(groups));

    //ASSERT_EQUAL(groups[0], vector<char>({ { 'b', 'a', 'c', 'a', 'd', 'e' }, { 'b','b','b', 'a', 'c', 'a', 'd', 'e', 'e', 'e' } }));
    //ASSERT_EQUAL(groups[1], vector<char>({ {'z','z','z'} }));
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestVectorSymbols);
    // RUN_TEST(tr, TestGroupingABC);
    // RUN_TEST(tr, TestGroupingReal);
    return 0;
}
