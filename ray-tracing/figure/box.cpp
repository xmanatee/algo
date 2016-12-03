//
// Created by manatee on 13.05.16.
//

#include "box.h"

Box operator | (const Box& a, const Box& b) {
    return Box(min(a.v1, b.v1), max(a.v2, b.v2));
}

Box operator | (const Box& a, const Vec3d& b) {
    return Box(min(a.v1, b), max(a.v2, b));
}

Box operator | (const Vec3d& b, const Box& a) {
    return Box(min(a.v1, b), max(a.v2, b));
}
