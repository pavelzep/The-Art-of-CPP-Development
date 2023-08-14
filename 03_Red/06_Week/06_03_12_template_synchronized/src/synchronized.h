#include <future>
#include <mutex>

using namespace std;

template <typename T>
class Synchronized {
public:
    explicit Synchronized(T initial = T()) :
        value(move(initial)) {
    }

    struct Access {
        lock_guard <mutex> g;
        T& ref_to_value;
    };

    Access GetAccess() {
        return Access{ lock_guard(m), value };
    }
private:
    T value;
    mutex m;
};