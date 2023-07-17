#include "test_runner.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <set>
#include <utility>
#include <vector>

#define MIN_PRIORITY 0

using namespace std;

template <typename T>
class PriorityCollection {
public:
    // тип, используемый для идентификаторов 
    using Id = size_t;

    // тип, используемый для приоритера 
    using Priority = int;


    // using It = typename set<T>::iterator;


    // Добавить объект с нулевым приоритетом
    // с помощью перемещения и вернуть его идентификатор
    Id Add(T object);

    // Добавить все элементы диапазона [range_begin, range_end)
    // с помощью перемещения, записав выданные им идентификаторы
    // в диапазон [ids_begin, ...)
    template <typename ObjInputIt, typename IdOutputIt>
    void Add(ObjInputIt range_begin, ObjInputIt range_end,
        IdOutputIt ids_begin);

    // Определить, принадлежит ли идентификатор какому-либо
    // хранящемуся в контейнере объекту
    bool IsValid(Id id) const;

    // Получить объект по идентификатору
    const T& Get(Id id) const;

    // Увеличить приоритет объекта на 1
    void Promote(Id id);

    // Получить объект с максимальным приоритетом и его приоритет
    pair<const T&, Priority> GetMax() const;

    // Аналогично GetMax, но удаляет элемент из контейнера
    pair<T, Priority> PopMax();

private:
    // Приватные поля и методы

    vector<T> objects;
    set<Priority> priorities;

    map<Id, Priority> id_to_priority;
    map<Priority,vector<Id>> priority_to_ids;

};


class StringNonCopyable : public string {
public:
    using string::string;  // Позволяет использовать конструкторы строки
    StringNonCopyable(const StringNonCopyable&) = delete;
    StringNonCopyable(StringNonCopyable&&) = default;
    StringNonCopyable& operator=(const StringNonCopyable&) = delete;
    StringNonCopyable& operator=(StringNonCopyable&&) = default;
};

void TestNoCopy() {
    PriorityCollection<StringNonCopyable> strings;
    const auto white_id = strings.Add("white");
    const auto yellow_id = strings.Add("yellow");
    const auto red_id = strings.Add("red");

    strings.Promote(yellow_id);
    for (int i = 0; i < 2; ++i) {
        strings.Promote(red_id);
    }
    strings.Promote(yellow_id);
    {
        const auto item = strings.PopMax();
        ASSERT_EQUAL(item.first, "red");
        ASSERT_EQUAL(item.second, 2);
    }
    {
        const auto item = strings.PopMax();
        ASSERT_EQUAL(item.first, "yellow");
        ASSERT_EQUAL(item.second, 2);
    }
    {
        const auto item = strings.PopMax();
        ASSERT_EQUAL(item.first, "white");
        ASSERT_EQUAL(item.second, 0);
    }
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestNoCopy);
    return 0;
}

template<typename T>
typename PriorityCollection<T>::Id PriorityCollection<T>::Add(T object) {
    objects.push_back(move(object);)
    

}

template<typename T>
bool PriorityCollection<T>::IsValid(Id id) const {
    return false;
}

template<typename T>
const T& PriorityCollection<T>::Get(Id id) const {

}

template<typename T>
void PriorityCollection<T>::Promote(Id id) {

}

template<typename T>
pair<const T&, typename PriorityCollection<T>::Priority> PriorityCollection<T>::GetMax() const {
    return pair<const T&, Priority>();
}

template<typename T>
pair<T, typename PriorityCollection<T>::Priority> PriorityCollection<T>::PopMax() {

    return pair<T, Priority>();
}

template<typename T>
template<typename ObjInputIt, typename IdOutputIt>
void PriorityCollection<T>::Add(ObjInputIt range_begin, ObjInputIt range_end, IdOutputIt ids_begin) {

}
