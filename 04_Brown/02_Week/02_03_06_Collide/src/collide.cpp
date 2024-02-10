
#include "geo2d.h"
#include "game_object.h"

#include "test_runner.h"

#include <vector>
#include <memory>

using namespace std;

template <typename T>
struct Collider : GameObject {
    bool Collide(const GameObject& that) const final {
        return that.CollideWith(static_cast<const T&>(*this));
    }
};

class Unit final : public Collider<Unit> {
public:
    Unit(geo2d::Point geo) : geo_(geo) {}
    geo2d::Point GetGeo() const { return geo_; }

    bool CollideWith(const Unit& that) const override;
    bool CollideWith(const Building& that) const override;
    bool CollideWith(const Tower& that) const override;
    bool CollideWith(const Fence& that) const override;
private:
    geo2d::Point geo_;
};

class Building : public Collider<Building> {
public:
    explicit Building(geo2d::Rectangle geo) :geo_(geo) {}
    geo2d::Rectangle GetGeo() const { return geo_; }

    bool CollideWith(const Unit& that) const override;
    bool CollideWith(const Building& that) const override;
    bool CollideWith(const Tower& that) const override;
    bool CollideWith(const Fence& that) const override;
private:
    geo2d::Rectangle geo_;
};

class Tower : public Collider<Tower> {
public:
    explicit Tower(geo2d::Circle geo) :geo_(geo) {}
    geo2d::Circle GetGeo() const { return geo_; }

    bool CollideWith(const Unit& that) const override;
    bool CollideWith(const Building& that) const override;
    bool CollideWith(const Tower& that) const override;
    bool CollideWith(const Fence& that) const override;
private:
    geo2d::Circle geo_;
};

class Fence : public Collider<Fence> {
public:
    explicit Fence(geo2d::Segment geo) :geo_(geo) {}
    geo2d::Segment GetGeo() const { return geo_; }

    bool CollideWith(const Unit& that) const override;
    bool CollideWith(const Building& that) const override;
    bool CollideWith(const Tower& that) const override;
    bool CollideWith(const Fence& that) const override;
private:
    geo2d::Segment geo_;
};

bool Collide(const GameObject& first, const GameObject& second) {
    return first.Collide(second);
}

#define COLLIDE_WITH(A, B)                      \
    bool A::CollideWith(const B& that) const {  \
    return geo2d::Collide(geo_,that.GetGeo());  \
    }                                  


#define COLLIDE_WITH_(A)         \
    COLLIDE_WITH(A, Unit) ;       \
    COLLIDE_WITH(A, Building);    \
    COLLIDE_WITH(A, Tower)  ;     \
    COLLIDE_WITH(A, Fence);

COLLIDE_WITH_(Unit)
COLLIDE_WITH_(Building)
COLLIDE_WITH_(Tower)
COLLIDE_WITH_(Fence)






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


