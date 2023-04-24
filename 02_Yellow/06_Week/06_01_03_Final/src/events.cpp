#include "events.h"

ostream& operator << (ostream& out, const Events& events) {
    for (const auto& evt : events.sortedEvents) {
        out << evt << endl;
    }
    return out;
}