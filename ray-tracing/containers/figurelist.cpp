//
// Created by manatee on 23.04.16.
//

#include <iostream>
#include "figurelist.h"

Intersection findFirstIntersection(const Line3d& beam, const FigureList& figures) {
    real minT = real_inf;
    Figure3d *minFigure;
    for (const auto& figure : figures) {
        if (figure->intersectsWith(beam)) {
            real t = figure->intersectWith(beam);
            if (t < minT) {
                minT = t;
                minFigure = figure;
            }
        }
    }
    return std::make_pair(minT, minFigure);
}
