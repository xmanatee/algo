//
// Created by manatee on 22.04.16.
//

#include "light.h"

std::pair<Vec3d, Vec3d> reflectAndRefract(const Vec3d& dir,
                                          const Vec3d& uniNormal,
                                          real bRefractionId,
                                          real mRefractionId) {
    real scalar = dir * uniNormal;
    real c;
    if (scalar > 0) c = mRefractionId / bRefractionId;
    else c = 1 / bRefractionId;
    Vec3d proj = uniNormal * scalar;
    return std::make_pair(2 * proj - dir, -proj + (proj - dir) * c);

}

Beam make_beam(const Vec3d& base, const Vec3d& dir) {
    Vec3d nDir = dir.normalized();
    Vec3d nBase = base + nDir * real_epsilon * 1e-1;

    //std::cerr << "len = " << nDir.len() << std::endl;
    return Beam(nBase, nDir);
}
