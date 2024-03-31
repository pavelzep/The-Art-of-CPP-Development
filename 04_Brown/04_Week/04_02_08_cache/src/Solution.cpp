#include "Common.h"

using namespace std;

class LruCache : public ICache {
public:
    LruCache(shared_ptr<IBooksUnpacker> books_unpacker, const Settings& settings)
        :books_unpacker_(books_unpacker), settings_(settings) {
    }

    BookPtr GetBook(const string& book_name) override {

        return books_unpacker_->UnpackBook(book_name);
        
    }

private:
    Settings settings_;
    shared_ptr<IBooksUnpacker> books_unpacker_;
};

unique_ptr<ICache> MakeCache(
    shared_ptr<IBooksUnpacker> books_unpacker,
    const ICache::Settings& settings
) {
    unique_ptr<ICache> cache;
    cache = make_unique<LruCache>(books_unpacker, settings);
    return cache;
}
