//
// Created by manatee on 23.04.16.
//

#ifndef GRAPHIC3D_TRAITS_H
#define GRAPHIC3D_TRAITS_H

#include "../utils/vec3d.h"
#include "../utils/vec2d.h"
#include "../lights/light.h"
#include "../color/color.h"

class Traits {
public:
    Color color;
    real alpha = 3.5;
    real reflectionRate, refractionRate, refractiveId;
    Traits(const Vec3d& _color,
           real _reflectionRate,
           real _refractionRate,
           real _refractiveId):
            color(_color),
            reflectionRate(_reflectionRate),
            refractionRate(_refractionRate),
            refractiveId(_refractiveId) { }

    Traits() { }

    Color getColorIn(const Vec2d& v) const {
        return color;
    }
};

const Traits TRAITS_RED(Color(1, 0, 0), 0, 0, 0);

#endif //GRAPHIC3D_TRAITS_H
