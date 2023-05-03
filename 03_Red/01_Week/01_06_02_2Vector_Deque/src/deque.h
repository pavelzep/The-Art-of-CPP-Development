#include <vector>
// #include <exception>

using namespace std;


template<typename T>
class Deque {
public:
    Deque() {

    }

    bool Empty() const {
        return (front.empty() && back.empty());
    }
    size_t Size() const {
        return front.size() + back.size();
    }

    T& At(size_t index) {
        // if (!(index < Size())) throw out_of_range("");
        if (index >= front.size()) {
            index -= front.size();
            return back.at(index);
        } else {
            return front.at(front.size() - index - 1);
        }
    }

    const T& At(size_t index) const {
        // if (!(index < Size())) throw out_of_range("");
        if (index >= front.size()) {
            index -= front.size();
            return back.at(index);
        } else {
            return front.at(front.size() - index - 1);
        }
    }

    T& operator[](size_t index) {
        if (index >= front.size()) {
            index -= front.size();
            return back[index];
        } else {
            return front[front.size() - index - 1];
        }
    }

    const T& operator[](size_t index) const {

        if (index >= front.size()) {
            index -= front.size();
            return back[index];
        } else {
            return front[front.size() - index - 1];
        }
    }

    T& Front() {
        if (front.empty()) return back.front();
        return front.back();
    }

    const T& Front() const {
        if (front.empty()) return back.front();
        return front.back();
    }

    T& Back() {
        if (back.empty()) return front.front();
        return back.back();
    }

    const T& Back() const {
        if (back.empty()) return front.front();
        return back.back();
    }

    void PushFront(const T& t) {
        front.push_back(t);
    }

    void PushBack(const T& t) {
        back.push_back(t);
    }


private:

    vector<T> front;
    vector<T> back;

};