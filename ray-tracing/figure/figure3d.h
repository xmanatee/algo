#ifndef _FIGURE3D_H_
#define _FIGURE3D_H_

#include "shape.h"
#include "traits.h"
#include "box.h"

class Sphere;

class Figure3d {
public:
    Shape shape;

    Traits traits;

    Box box;

    Figure3d(const Shape _shape): shape(_shape), traits(TRAITS_RED) {}
    Figure3d(const Shape _shape, const Traits& _traits): shape(_shape), traits(_traits) {}

    virtual Vec3d getNormalIn(const Vec3d &v) const = 0;

    virtual Vec3d getColorIn(const Vec3d &v) const = 0;

    virtual bool intersectsWith(const Line3d& line) const = 0;

    virtual real intersectWith(const Line3d& line) const = 0;
};

#endif // _FIGURE3D_H_