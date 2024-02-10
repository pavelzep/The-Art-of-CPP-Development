#pragma once

#include "geo2d.h"
#include "game_object.h"

using namespace std;

template <typename T, typename G>
struct Collider : GameObject {
    explicit Collider(G geo) : geo_(geo) {}
    const G& GetGeo() const { return geo_; }
    bool Collide(const GameObject& that) const final {
        return that.CollideWith(static_cast<const T&>(*this));
    }
    bool CollideWith(const Unit& that) const override;
    bool CollideWith(const Building& that) const override;
    bool CollideWith(const Tower& that) const override;
    bool CollideWith(const Fence& that) const override;
protected:
    G geo_;
};

#define GAME_OBJECT_CLASS(OBJ_t,GEO_t)                            \
class OBJ_t: public Collider <OBJ_t, geo2d::GEO_t> {        \
    public:                                                 \
    explicit OBJ_t(geo2d::GEO_t geo) :Collider(geo) {}      \
};                                                          \
template <typename T, typename G>                           \
bool Collider<T, G>::CollideWith(const OBJ_t& that) const { \
    return geo2d::Collide(geo_,that.GetGeo());              \
    }  

GAME_OBJECT_CLASS(Unit, Point);
GAME_OBJECT_CLASS(Building, Rectangle);
GAME_OBJECT_CLASS(Tower, Circle);
GAME_OBJECT_CLASS(Fence, Segment);