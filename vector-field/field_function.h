//
// Created by manatee on 07.11.16.
//

#ifndef RAIC_2016_FIELD_FUNCTION_H
#define RAIC_2016_FIELD_FUNCTION_H

#include <functional>

#include "vec2.h"

class Gravity : public std::function<Vec2d(const Vec2d&, const Vec2d&)> {
public:
    Gravity(double _g, double _deg = 2): g(_g), deg(_deg) {}
    Vec2d operator()(const Vec2d& center, const Vec2d& v) {
        Vec2d r = v - center;
        return -g * r / pow(r.len(), deg + 1);
    }
private:
    double g, deg;
};

#endif //RAIC_2016_FIELD_FUNCTION_H
