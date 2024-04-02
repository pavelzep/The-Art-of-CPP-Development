#include "Common.h"
#include <deque>
#include <algorithm>
#include <mutex>

using namespace std;

class LruCache : public ICache {
public:
    LruCache(
        shared_ptr<IBooksUnpacker> books_unpacker,
        const Settings& settings)
        :books_unpacker_(books_unpacker), settings_(settings) {
    }

    BookPtr GetBook(const string& book_name) override {
        lock_guard<mutex> g(m);
        std::deque<ICache::BookPtr>::iterator it = findBook(book_name);
        if (it != store.end()) {
            BookPtr b_ptr_ = *it;
            store.erase(it);
            store.push_front(b_ptr_);
            return store.front();
        }

        BookPtr b_ptr = books_unpacker_->UnpackBook(book_name);
        size_t b_size = b_ptr.get()->GetContent().size();

        while (settings_.max_memory - memory_used_by_books_ < b_size) {
            if (!store.empty()) {
                BookPtr b_ptr_to_remove = store.back();
                memory_used_by_books_ -= b_ptr_to_remove.get()->GetContent().size();
                store.pop_back();
            } else {
                break;
            }
        }

        if (b_size <= settings_.max_memory) {
            memory_used_by_books_ += b_size;
            store.push_front(b_ptr);
        }
        return b_ptr;
    }

private:
    std::deque<ICache::BookPtr>::iterator findBook(const string& book_name) {
        auto book_ptr = find_if(store.begin(), store.end(), [&book_name](BookPtr& ptr) {
            return ptr->GetName() == book_name;});
        return book_ptr;
    }

    Settings settings_;
    shared_ptr<IBooksUnpacker> books_unpacker_;
    deque<BookPtr> store;
    size_t memory_used_by_books_ = 0;
    mutex m;
};

unique_ptr<ICache> MakeCache(
    shared_ptr<IBooksUnpacker> books_unpacker,
    const ICache::Settings& settings
) {
    return make_unique<LruCache>(books_unpacker, settings);
}
