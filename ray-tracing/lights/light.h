//
// Created by manatee on 22.04.16.
//

#ifndef GRAPHIC3D_LIGHT_H
#define GRAPHIC3D_LIGHT_H

#include "../utils/vec3d.h"
#include "../utils/line3d.h"

typedef Vec3d Light;

const Light
        LIGHT_WHITE(1, 1, 1),
        LIGHT_RED(1, 0, 0),
        LIGHT_GREEN(0, 1, 0),
        LIGHT_BLUE(0, 0, 1),
        LIGHT_YELLOW(1, 1, 0),
        LIGHT_CYAN(0, 1, 1),
        LIGHT_MAGENTO(1, 0, 1),
        LIGHT_BLACK(0, 0, 0);

const real ambientLightPower = 1;

std::pair<Vec3d, Vec3d> reflectAndRefract(const Vec3d& dir,
                                          const Vec3d& uniNormal,
                                          real bRefractionId,
                                          real mRefractionId);

typedef Line3d Beam;

Beam make_beam(const Vec3d& base, const Vec3d& dir);

#endif //GRAPHIC3D_LIGHT_H
