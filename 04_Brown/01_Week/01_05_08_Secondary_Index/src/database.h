#include <iostream>
#include <map>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <iterator>
#include <deque>

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

    deque<Record> store;

    map<string, Record> id_to_Rec;
    
    // multimap <int, map<string, Record>::iterator> stamps;
    multimap <int, pair<const string*, Record*>> stamps;
    multimap <int, pair<const string*, Record*>> karmas;
    multimap <string*, pair<const string*, Record*>> users;

    void Test(){
        auto it = store.begin();
        auto r = *it;
        auto t = &r;
    };

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
 return false;
}

const Record* Database::GetById(const string& id) const {
    return nullptr;
}

bool Database::Erase(const string& id) {

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
