#include "test_runner.h"

#include <iostream>
#include <map>
#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;

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
// Реализуйте этот класс
class Database {


    map<string, Record> store;
    multimap <int, map<string, Record>::iterator> stamps;
    multimap <int, map<string, Record>::iterator> karmas;
    multimap <string, map<string, Record>::iterator> users;

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

bool Database::Put(const Record& record) {

    auto _pair = store.insert(pair(record.id, record));
    if (_pair.second == true) {
        stamps.insert(pair(record.timestamp, _pair.first));
        karmas.insert(pair(record.karma, _pair.first));
        users.insert(pair(record.user, _pair.first));
        return true;
    } else return false;
    // auto it = store.find(record.id);
    // if (it == store.end()) {
    //     store.insert(pair(record.id, record));
    //     return true;
    // } else {
    //     return false;
    // }

}

const Record* Database::GetById(const string& id) const {
    auto it = store.find(id);
    if (it == store.end())
        return nullptr;
    else {
        return &it->second;
    }
}

bool Database::Erase(const string& id) {
    auto it = store.find(id);
    if (it == store.end())
        return false;
    else {
        
            auto range = stamps.equal_range(it->second.timestamp);

            auto pair = remove_if(range.first, range.second,
                [&id](multimap<int, map<string, Record>::iterator>::iterator& item) { return item->second->second.id==id; });
            // stamps.erase(pair);
        
        // store.erase(it);

        return true;
    }

    return false;
}

template<typename Callback>
void Database::RangeByTimestamp(int low, int high, Callback callback) const {

}

template<typename Callback>
void Database::RangeByKarma(int low, int high, Callback callback) const {
}

template<typename Callback>
void Database::AllByUser(const string& user, Callback callback) const {
}
