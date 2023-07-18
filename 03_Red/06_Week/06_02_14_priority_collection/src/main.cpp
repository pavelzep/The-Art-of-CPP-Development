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

    // struct Object{
    //     T object;
    //     Priority priority;
    // }

    using Object = struct { T object; Priority priority; };

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

    vector<Object> objects;
    map<Priority, set<Id>> priority_to_ids;

    Priority GetMaxPriority()const;
    Id GetMaxPriorityId(const Priority priority) const;
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

    objects.push_back({ move(object),MIN_PRIORITY });
    Id id = objects.size() - 1;
    priority_to_ids[MIN_PRIORITY].insert(id);
    return id;
}


template<typename T>
bool PriorityCollection<T>::IsValid(Id id) const {
    bool result = false;
    if (objects[id].priority != -1) result = true;
    return result;
}

template<typename T>
const T& PriorityCollection<T>::Get(Id id) const {
    return objects[id].object;
}

template<typename T>
void PriorityCollection<T>::Promote(Id id) {

    Priority priority = objects[id].priority++;
    priority_to_ids[priority].erase(id);
    if (priority_to_ids[priority].size() == 0) {
        priority_to_ids.erase(priority);
    }
    priority_to_ids[++priority].insert(id);
}

template<typename T>
pair<const T&, typename PriorityCollection<T>::Priority> PriorityCollection<T>::GetMax() const {

    auto max_priority = GetMaxPriority();
    auto max_priority_id = GetMaxPriorityId(max_priority);
    return { objects.at(max_priority_id).object, max_priority };

}

template<typename T>
pair<T, typename PriorityCollection<T>::Priority> PriorityCollection<T>::PopMax() {

    Priority max_priority = GetMaxPriority();
    Id max_priority_id = GetMaxPriorityId(max_priority);
    priority_to_ids.rbegin()->second.erase(max_priority_id);

    if (priority_to_ids[max_priority].size() == 0) {
        priority_to_ids.erase(max_priority);
    }

    objects[max_priority_id].priority = -1;

    return{ move(objects.at(max_priority_id).object), max_priority };
}

template<typename T>
typename PriorityCollection<T>::Priority PriorityCollection<T>::GetMaxPriority() const {
    return priority_to_ids.rbegin()->first;
}

template<typename T>
typename PriorityCollection<T>::Id PriorityCollection<T>::GetMaxPriorityId(const Priority priority) const {
    return *priority_to_ids.at(priority).rbegin();
}

template<typename T>
template<typename ObjInputIt, typename IdOutputIt>
void PriorityCollection<T>::Add(ObjInputIt range_begin, ObjInputIt range_end, IdOutputIt ids_begin) {
    auto it = range_begin;
    while (it != range_end) {
        *ids_begin = Add(move(*it));
        ++ids_begin;
        ++it;
    }
}
