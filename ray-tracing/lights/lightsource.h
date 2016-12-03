#ifndef _LIGHTSOURCE_H_
#define _LIGHTSOURCE_H_

#include "../utils/vec3d.h"
#include "light.h"

class LightSource {
public:
    Vec3d loc;
    real power;
    LightSource(const Vec3d& _loc, real _power): loc(_loc), power(_power) {}
};

#endif // _LIGHTSOURCE_H_