#include <vector>
using namespace std;

template<typename Iterator>
class IteratorRange {
private:
    Iterator first, last;

public:
    IteratorRange(Iterator f, Iterator l)
        : first(f)
        , last(l) {
    }

    Iterator begin() const {
        return first;
    }

    Iterator end() const {
        return last;
    }

    //возвращает размер страницы
    size_t size() const {
        return end() - begin();
    }
};

template <typename Iterator>
class Paginator {
private:
    vector <IteratorRange<Iterator>> pages;

public:
    Paginator(Iterator begin, Iterator end, size_t page_size) {
        pages.push_back();
    }

    // возвращает количество страниц
    size_t size() const {
        return pages.size();
    }

    auto begin() const {
        return pages.begin();
    }

    auto end() const {
        return pages.end();
    }
};

template <typename Container>
auto Paginate(Container& container, size_t page_size) {
    return Paginator(container.begin(), container.end(), page_size);
};