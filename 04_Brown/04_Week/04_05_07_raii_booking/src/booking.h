#pragma once

namespace RAII {

    template<typename T>
    struct Booking {
        T* provider;
        int counter;

        Booking() = default;
        Booking(const Booking&) = delete;
        Booking(Booking&&) = default;

        Booking& operator=(const Booking&) = delete;
        Booking& operator=(Booking&&) = default;

        ~Booking() {
            --provider->counter;
        }
    };

}