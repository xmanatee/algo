//
// Created by manatee on 23.04.16.
//

#ifndef GRAPHIC3D_SCREENCOLOR_H_H
#define GRAPHIC3D_SCREENCOLOR_H_H

#include "../utils/vec3d.h"
#include "../utils/numeric.h"

class RGB {
public:
    small r, g, b;
    RGB(small _r, small _g, small _b): r(_r), g(_g), b(_b) { }
    RGB(): r(0), g(0), b(0) { };
    Vec3d toColor();
};

std::ostream& operator << (std::ostream& out, const RGB& rgb);
std::istream& operator >> (std::istream& in, RGB& rgb);

const RGB
        WHITE(small_max, small_max, small_max),
        RED(small_max, 0, 0),
        GREEN(0, small_max, 0),
        BLUE(0, 0, small_max),
        YELLOW(small_max, small_max, 0),
        CYAN(0, small_max, small_max),
        MAGENTO(small_max, 0, small_max),
        BLACK(0, 0, 0);

#endif //GRAPHIC3D_SCREENCOLOR_H_H
