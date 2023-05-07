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

        for (Iterator it = begin;it < end;it = next(it, page_size)) {
            IteratorRange page(it, min(next(it, page_size),end));
            pages.push_back(page);
        }

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