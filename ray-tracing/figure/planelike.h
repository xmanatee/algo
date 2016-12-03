//
// Created by manatee on 13.05.16.
//

#ifndef GRAPHIC3D_PLANELIKE_H
#define GRAPHIC3D_PLANELIKE_H

#include <cmath>
#include <vector>

#include "figure3d.h"

#include "../utils/geom.h"

class Planelike : public Figure3d {
private:
    void finishInitialization() {
        loc = v[0];
        normal = (v[0] - v[1]) ^ (v[2] - v[1]);
        normal.normalize();

        e1 = (v[0] - v[1]).normalized();
        e2 = normal ^ e1;

        box.v1 = v[0];
        box.v2 = v[0];
        for (int i = 1; i < v.size(); ++i) {
            box = box | v[i];
        }
    }
public:
    std::vector<Vec3d> v;
    Vec3d loc, normal;
    Vec3d e1, e2;

    Planelike(const Vec3d &v1, const Vec3d &v2, const Vec3d &v3):
            Figure3d(PLANELIKE) {
        v.push_back(v1);
        v.push_back(v2);
        v.push_back(v3);

        finishInitialization();
    }

    Planelike(const Vec3d &v1, const Vec3d &v2, const Vec3d &v3, const Vec3d &v4):
            Figure3d(PLANELIKE) {
        v.push_back(v1);
        v.push_back(v2);
        v.push_back(v3);
        v.push_back(v4);

        finishInitialization();
    }

    Vec3d getNormalIn(const Vec3d &v) const override {
        return normal;
    }

    Color getColorIn(const Vec3d& v) const override {
        return traits.getColorIn(Vec2d((v - loc) * e1, (v - loc) * e2));
    }

    bool intersectsWith(const Line3d& line) const override {
        bool b = det3d(v.back() - line.base, v.front() - line.base, line.dir) > 0;
        for (int i = 1; i < v.size(); ++i) {
            bool b2 = det3d(v[i - 1] - line.base, v[i] - line.base, line.dir) > 0;
            if (b2 ^ b) return false;
        }
        return true;
    }

    real intersectWith(const Line3d& line) const override {
        if (!intersectsWith(line)) return real_inf;

        real t = distToPlane(line.base, line.dir, normal, loc);

        if (lessOrEqual(t, 0)) return real_inf;

        return t;
    }

};

#endif //GRAPHIC3D_PLANELIKE_H
