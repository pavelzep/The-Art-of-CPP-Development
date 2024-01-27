#pragma once

#include <map>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <iterator>

using namespace std;

template <typename It>
class IteratorRange {
public:
    IteratorRange(It first, It last) : first(first), last(last) {}
    It begin() const { return first; }
    It end() const { return last; }
    size_t size() const { return last - first; }

private:
    It first, last;
};

template <typename Container>
auto Head(Container& c, int top) {
    return IteratorRange(begin(c), begin(c) + min<size_t>(max(top, 0), c.size()));
}

struct Record {
    string id;
    string title;
    string user;
    int timestamp;
    int karma;
};

struct Record_its {
    multimap<int, Record*>::iterator timestamp_it;
    multimap<int, Record*>::iterator karma_it;
    multimap<string, Record*>::iterator user_it;
};

class Database {

    map<string, Record> id_to_Rec;

    multimap<int, Record*> timestamps;
    multimap<int, Record*> karmas;
    multimap<string, Record*> users;

    map<string, Record_its> store;

public:
    bool Put(const Record& record);
    const Record* GetById(const string& id) const;
    bool Erase(const string& id);

    template <typename Callback>
    void RangeByTimestamp(int low, int high, Callback callback) const;

    template <typename Callback>
    void RangeByKarma(int low, int high, Callback callback) const;

    template <typename Callback>
    void AllByUser(const string& user, Callback callback) const;
};

bool Database::Put(const Record& record) {

    auto pair_ = id_to_Rec.insert(pair(record.id, record));
    if (!pair_.second) return false;
    Record* rec_ = &((*(pair_.first)).second);

    Record_its its;

    its.timestamp_it = timestamps.insert(pair(rec_->timestamp, rec_));
    its.karma_it = karmas.insert(pair(rec_->karma, rec_));
    its.user_it = users.insert(pair(rec_->user, rec_));

    store.insert(pair(record.id, its));
    return true;
}

const Record* Database::GetById(const string& id) const {
    auto it = id_to_Rec.find(id);
    if (it == id_to_Rec.end()) return nullptr;
    return &((*it).second);
}

bool Database::Erase(const string& id) {
    auto it = id_to_Rec.find(id);
    if (it == id_to_Rec.end()) return false;
    Record* pRecord = &it->second;

    auto its = store.find(id);

    timestamps.erase(its->second.timestamp_it);
    karmas.erase(its->second.karma_it);
    users.erase(its->second.user_it);

    store.erase(its);

    id_to_Rec.erase(it);

    return true;
}

template<typename Callback>
void Database::RangeByTimestamp(int low, int high, Callback callback) const {
    auto it_low = timestamps.lower_bound(low);
    auto it_high = timestamps.upper_bound(high);
    for (const auto& item : IteratorRange(it_low, it_high))
        if (!callback(*item.second)) return;
}

template<typename Callback>
void Database::RangeByKarma(int low, int high, Callback callback) const {
    auto it_low = karmas.lower_bound(low);
    auto it_high = karmas.upper_bound(high);
    for (const auto& item : IteratorRange(it_low, it_high))
        if (!callback(*item.second)) return;
}

template<typename Callback>
void Database::AllByUser(const string& user, Callback callback) const {
    auto it_low = users.lower_bound(user);
    auto it_high = users.upper_bound(user);
    for (const auto& item : IteratorRange(it_low, it_high))
        if (!callback(*item.second)) return;
}
