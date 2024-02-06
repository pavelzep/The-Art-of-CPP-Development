#include "geo2d.h"
#include "game_object.h"

using namespace std;

class Unit : public GameObject {
public:
    explicit Unit(geo2d::Point position) :position_(position) {}
    geo2d::Point GetGeo() const { return position_; }
    bool Collide(const GameObject& that) const override;
    bool CollideWith(const Unit& that) const override;
    bool CollideWith(const Building& that) const override;
    bool CollideWith(const Tower& that) const override;
    bool CollideWith(const Fence& that) const override;

private:
    geo2d::Point position_;
};

class Building : public GameObject {
public:
    explicit Building(geo2d::Rectangle geometry) :geometry_(geometry) {}
    geo2d::Rectangle GetGeo() const { return geometry_; }
    bool Collide(const GameObject& that) const override;
    bool CollideWith(const Unit& that) const override;
    bool CollideWith(const Building& that) const override;
    bool CollideWith(const Tower& that) const override;
    bool CollideWith(const Fence& that) const override;
private:
    geo2d::Rectangle geometry_;
};

class Tower : public GameObject {
public:
    explicit Tower(geo2d::Circle geometry) :geometry_(geometry) {}
    geo2d::Circle GetGeo() const { return geometry_; }
    bool Collide(const GameObject& that) const override;
    bool CollideWith(const Unit& that) const override;
    bool CollideWith(const Building& that) const override;
    bool CollideWith(const Tower& that) const override;
    bool CollideWith(const Fence& that) const override;
private:
    geo2d::Circle geometry_;
};

class Fence : public GameObject {
public:
    explicit Fence(geo2d::Segment geometry) :geometry_(geometry) {}
    geo2d::Segment GetGeo() const { return geometry_; }
    bool Collide(const GameObject& that) const override;
    bool CollideWith(const Unit& that) const override;
    bool CollideWith(const Building& that) const override;
    bool CollideWith(const Tower& that) const override;
    bool CollideWith(const Fence& that) const override;
private:
    geo2d::Segment geometry_;
};

bool Collide(const GameObject& first, const GameObject& second) {
    return first.Collide(second);
}