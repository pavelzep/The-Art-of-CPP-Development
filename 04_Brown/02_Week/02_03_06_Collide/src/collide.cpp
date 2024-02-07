#include "geo2d.h"
#include "game_object.h"

using namespace std;

// Создаём шаблон класса Collider, только в нём будет переопределяться метод Collide 
template <typename T>
struct Collider : GameObject {
    bool Collide(const GameObject& that) const final {
        // Статически приводим тип *this к типу const T&, потому что мы знаем, 
        // что T — наш наследник (см. ниже) 
        return that.CollideWith(static_cast<const T&>(*this));
    }
};

class Unit final : public Collider<Unit> { 
public: 
  Unit(geo2d::Point position): position_(position) {}
    geo2d::Point GetGeo() const { return position_; }

    bool CollideWith(const Unit& that) const override{ return false;}
    bool CollideWith(const Building& that) const override{ return false;}
    bool CollideWith(const Tower& that) const override{ return false;}
    bool CollideWith(const Fence& that) const override{ return false;}

private:
    geo2d::Point position_;
};

class Building : public Collider<Building>  {
public:
    explicit Building(geo2d::Rectangle geometry) :geometry_(geometry) {}
    geo2d::Rectangle GetGeo() const { return geometry_; }

    bool CollideWith(const Unit& that) const override{ return false;}
    bool CollideWith(const Building& that) const override{ return false;}
    bool CollideWith(const Tower& that) const override{ return false;}
    bool CollideWith(const Fence& that) const override{ return false;}
private:
    geo2d::Rectangle geometry_;
};

class Tower : public Collider<Tower> {
public:
    explicit Tower(geo2d::Circle geometry) :geometry_(geometry) {}
    geo2d::Circle GetGeo() const { return geometry_; }

    bool CollideWith(const Unit& that) const override{ return false;}
    bool CollideWith(const Building& that) const override{ return false;}
    bool CollideWith(const Tower& that) const override{ return false;}
    bool CollideWith(const Fence& that) const override{ return false;}
private:
    geo2d::Circle geometry_;
};

class Fence : public Collider<Fence> {
public:
    explicit Fence(geo2d::Segment geometry) :geometry_(geometry) {}
    geo2d::Segment GetGeo() const { return geometry_; }

    bool CollideWith(const Unit& that) const override{ return false;}
    bool CollideWith(const Building& that) const override{ return false;}
    bool CollideWith(const Tower& that) const override{ return false;}
    bool CollideWith(const Fence& that) const override{ return false;}
private:
    geo2d::Segment geometry_;
};

bool Collide(const GameObject& first, const GameObject& second) {
    return first.Collide(second);
}