
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
    struct ConstAccess {
        lock_guard <mutex> g;
        const T& ref_to_value;
    };

    Access GetAccess() {
        return Access{ lock_guard(m), value };
    }

    ConstAccess GetAccess() const {
        return ConstAccess{ lock_guard(m), value };
    }

private:
    T value;
    mutable mutex m;
};

