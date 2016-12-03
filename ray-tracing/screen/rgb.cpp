//
// Created by manatee on 23.04.16.
//

#include "rgb.h"

std::ostream& operator << (std::ostream& out, const RGB& rgb) {
    out << "(r" << rgb.r << ",g" << rgb.g << ",b" << rgb.b << ")";
    return out;
}

std::istream& operator >> (std::istream& in, RGB& rgb) {
    int r, g, b;
    in >> r >> g >> b;
    rgb.r = r;
    rgb.g = g;
    rgb.b = b;
    return in;
}


Vec3d RGB::toColor() {
    return Vec3d(r / 255.0, g / 255.0, b / 255.0);
}