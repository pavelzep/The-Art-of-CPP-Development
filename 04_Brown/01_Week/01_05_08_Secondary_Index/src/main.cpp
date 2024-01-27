#include "test_runner.h"


// #include "database.h"
// Start "database.h"
// #pragma once

#include <iostream>
#include <map>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <iterator>
#include <deque>

using namespace std;



// #include "iterator_range.h"
// Start "iterator_range.h"
// #pragma once
// #include <algorithm>

template <typename It>
class IteratorRange {
public:
    IteratorRange(It first, It last) : first(first), last(last) {
    }

    It begin() const {
        return first;
    }

    It end() const {
        return last;
    }

    size_t size() const {
        return last - first;
    }

private:
    It first, last;
};

template <typename Container>
auto Head(Container& c, int top) {
    return IteratorRange(begin(c), begin(c) + min<size_t>(max(top, 0), c.size()));
}
//End "iterator_range.h"


// typedef string  id_t;
// typedef string  title_t;
typedef string  user_t;
typedef int     timestamp_t;
typedef int     karma_t;


struct Record {
    string id;
    string title;
    string user;
    int timestamp;
    int karma;
};

bool operator < (const Record& l, const Record& r) {
    return l.id < r.id;
};


struct Record_its {
    multimap<timestamp_t, Record*>::iterator timestamp_it;
    multimap<karma_t, Record*>::iterator karma_it;
    multimap<user_t, Record*>::iterator user_it;
};

// Реализуйте этот класс
class Database {

    map<string, Record> id_to_Rec;

    multimap<timestamp_t, Record*> timestamps;
    multimap<karma_t, Record*> karmas;
    multimap<user_t, Record*> users;

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

    // pair<map<const string, Record>::iterator, bool> it = id_to_Rec.insert(pair(record.id, record));
    // pair<const string, Record> pair_ = *(it.first);
    // Record* rec_ = &(pair_.second);

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

    // {
    //     auto range = timestamps.equal_range(pRecord->timestamp);
    //     // auto pf = range.first;
    //     // auto f = *pf;
    //     // auto pRec = f.second;
    //     // id_t id_ = pRec->id;
    //     auto it_timestamp = find_if(range.first, range.second, [&id](auto& pair_) {
    //         return pair_.second->id == id;
    //         });
    //     timestamps.erase(it_timestamp);
    // }
    // {
    //     auto range = karmas.equal_range(pRecord->karma);
    //     auto it_karma = find_if(range.first, range.second, [&id](auto& pair_) {
    //         return pair_.second->id == id;
    //         });
    //     karmas.erase(it_karma);
    // }
    // {
    //     auto range = users.equal_range(pRecord->user);
    //     auto it_user = find_if(range.first, range.second, [&id](auto& pair_) {
    //         return pair_.second->id == id;
    //         });
    //     users.erase(it_user);
    // }
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

//End "database.h"

using namespace std;

void TestRangeBoundaries() {

    const int good_karma = 1000;
    const int bad_karma = -10;

    Database db;
    db.Put({ "id1", "Hello there", "master", 1536107260, good_karma });
    db.Put({ "id2", "O>>-<", "general2", 1536107260, bad_karma });

    int count = 0;
    db.RangeByKarma(bad_karma, good_karma, [&count](const Record&) {
        ++count;
        return true;
        });

    ASSERT_EQUAL(2, count);

}

void TestSameUser() {
    Database db;
    db.Put({ "id1", "Don't sell", "master", 1536107260, 1000 });
    db.Put({ "id2", "Rethink life", "master", 1536107260, 2000 });

    int count = 0;
    db.AllByUser("master", [&count](const Record&) {
        ++count;
        return true;
        });

    ASSERT_EQUAL(2, count);
}

void TestReplacement() {
    const string final_body = "Feeling sad";

    Database db;
    db.Put({ "id", "Have a hand", "not-master", 1536107260, 10 });
    db.Erase("id");
    db.Put({ "id", final_body, "not-master", 1536107260, -10 });

    auto record = db.GetById("id");
    ASSERT(record != nullptr);
    ASSERT_EQUAL(final_body, record->title);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestRangeBoundaries);
    RUN_TEST(tr, TestSameUser);
    RUN_TEST(tr, TestReplacement);
    return 0;

}
