#pragma once
#include <utility>
#include <iostream>

namespace RAII {

    template<class Provider>
    class Booking {
    public:
        Booking(Provider* provider, int id) : provider_(provider), id_(id) {}

        Booking(const Booking&) = delete;
        Booking& operator=(const Booking&) = delete;

        Booking(Booking&& other) {
            // std::cout << "\n\n\nconst:\nother =" << &other << "\n               this = " << this;
            std::swap(provider_, other.provider_);
            std::swap(id_, other.id_);

        }

        Booking& operator=(Booking&& other) {
            std::swap(provider_, other.provider_);
            std::swap(id_, other.id_);
            return *this;
        }

        ~Booking() {
            // std::cout << "\n\ndestr: this = " << this;
            if (provider_)
                provider_->CancelOrComplete(*this);
        }

    private:
        Provider* provider_ = nullptr;
        int id_;
    };

}