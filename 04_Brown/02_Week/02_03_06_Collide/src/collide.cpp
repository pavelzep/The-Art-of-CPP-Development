#include "geo2d.h"
#include "game_object.h"

#include "test_runner.h"

#include <vector>
#include <memory>

using namespace std;

bool Collide(const GameObject& first, const GameObject& second) {
    return first.Collide(second);
}

template <typename T, typename G>
struct Collider : GameObject {
    explicit Collider(G geo);
    const G& GetGeo() const;
    bool Collide(const GameObject& that) const final;
    bool CollideWith(const Unit& that) const override;
    bool CollideWith(const Building& that) const override;
    bool CollideWith(const Tower& that) const override;
    bool CollideWith(const Fence& that) const override;
protected:
    G geo_;
};

template<typename T, typename G>
Collider<T, G>::Collider(G geo) : geo_(geo) {}

template<typename T, typename G>
const G& Collider<T, G>::GetGeo() const { return geo_; }

template <typename T, typename G>
bool Collider<T, G>::Collide(const GameObject& that) const {
    return that.CollideWith(static_cast<const T&>(*this));
}

#define GAME_OBJECT(OBJ_t,GEO_t)                            \
class OBJ_t: public Collider <OBJ_t, geo2d::GEO_t> {        \
    public:                                                 \
    explicit OBJ_t(geo2d::GEO_t geo) :Collider(geo) {}      \
};

GAME_OBJECT(Unit, Point);
GAME_OBJECT(Building, Rectangle);
GAME_OBJECT(Tower, Circle);
GAME_OBJECT(Fence, Segment);

#define COLLIDE_WITH(OBJ_t)                      \
template <typename T, typename G>               \
bool Collider<T, G>::CollideWith(const OBJ_t& that) const {  \
    return geo2d::Collide(geo_,that.GetGeo());  \
    }                                  

COLLIDE_WITH(Unit)
COLLIDE_WITH(Building)
COLLIDE_WITH(Tower)
COLLIDE_WITH(Fence)



void TestAddingNewObjectOnMap() {
    using namespace geo2d;

    const vector<shared_ptr<GameObject>> game_map = {
      make_shared<Unit>(Point{3, 3}),
      make_shared<Unit>(Point{5, 5}),
      make_shared<Unit>(Point{3, 7}),
      make_shared<Fence>(Segment{{7, 3}, {9, 8}}),
      make_shared<Tower>(Circle{Point{9, 4}, 1}),
      make_shared<Tower>(Circle{Point{10, 7}, 1}),
      make_shared<Building>(Rectangle{{11, 4}, {14, 6}})
    };

    for (size_t i = 0; i < game_map.size(); ++i) {
        Assert(
            Collide(*game_map[i], *game_map[i]),
            "An object doesn't collide with itself: " + to_string(i)
        );

        for (size_t j = 0; j < i; ++j) {
            Assert(
                !Collide(*game_map[i], *game_map[j]),
                "Unexpected collision found " + to_string(i) + ' ' + to_string(j)
            );
        }
    }

    auto new_warehouse = make_shared<Building>(Rectangle{ {4, 3}, {9, 6} });
    ASSERT(!Collide(*new_warehouse, *game_map[0]));
    ASSERT(Collide(*new_warehouse, *game_map[1]));
    ASSERT(!Collide(*new_warehouse, *game_map[2]));
    ASSERT(Collide(*new_warehouse, *game_map[3]));
    ASSERT(Collide(*new_warehouse, *game_map[4]));
    ASSERT(!Collide(*new_warehouse, *game_map[5]));
    ASSERT(!Collide(*new_warehouse, *game_map[6]));

    auto new_defense_tower = make_shared<Tower>(Circle{ {8, 2}, 2 });
    ASSERT(!Collide(*new_defense_tower, *game_map[0]));
    ASSERT(!Collide(*new_defense_tower, *game_map[1]));
    ASSERT(!Collide(*new_defense_tower, *game_map[2]));
    ASSERT(Collide(*new_defense_tower, *game_map[3]));
    ASSERT(Collide(*new_defense_tower, *game_map[4]));
    ASSERT(!Collide(*new_defense_tower, *game_map[5]));
    ASSERT(!Collide(*new_defense_tower, *game_map[6]));
}

void TestAll() {
    TestRunner tr;
    RUN_TEST(tr, TestAddingNewObjectOnMap);
}

int main() {
    TestAll();
    return 0;
}


