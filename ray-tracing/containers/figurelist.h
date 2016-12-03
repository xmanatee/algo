#ifndef _FIGURELIST_H_
#define _FIGURELIST_H_

#include <vector>
#include <utility>

#include "../figure/figure3d.h"

typedef std::vector<Figure3d*> FigureList;

typedef std::pair<real, Figure3d*> Intersection;

Intersection findFirstIntersection(const Line3d& beam, const FigureList& figures);

#endif // _FIGURELIST_H_