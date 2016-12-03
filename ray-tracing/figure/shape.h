#ifndef _SHAPE3D_H_
#define _SHAPE3D_H_

#include <ostream>

enum Shape {SPHERE, PLANE, PLANELIKE};

std::ostream& operator << (std::ostream& out, const Shape& shape);

#endif // _SHAPE3D_H_