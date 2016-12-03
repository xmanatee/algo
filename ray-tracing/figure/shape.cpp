//
// Created by manatee on 23.04.16.
//

#include "shape.h"

std::ostream& operator << (std::ostream& out, const Shape& shape) {
    if (shape == SPHERE) out << "SPHERE";
    else if (shape == PLANE) out << "PLANE";
    else if (shape == PLANELIKE) out << "PLANELIKE";
    return out;
}
