//
// Created by manatee on 09.05.16.
//


#include <fstream>
#include <cassert>
#include <iostream>
#include <map>
#include "reader.h"
#include "../camera.h"
#include "../color/color.h"
#include "../figure/planelike.h"
#include "../figure/plane.h"
#include "../figure/sphere.h"

Reader::Reader() {}

std::pair<Camera, Scene> Reader::readStl(const std::string &filename) const {
    Scene scene;
    Camera camera;

    std::ifstream fin(filename);
    std::string s;
    real x, y, z;

    fin >> s;
    assert(s == "solid");
    fin >> s >> s;
    while (s != "endsolid") {
        assert(s == "facet");
        fin >> s >> x >> y >> z;
        Vec3d n(x, y, z);
        fin >> s >> s;
        fin >> s >> x >> y >> z;
        Vec3d a(x, y, z);
        fin >> s >> x >> y >> z;
        Vec3d b(x, y, z);
        fin >> s >> x >> y >> z;
        Vec3d c(x, y, z);
        fin >> s >> s >> s;
        scene.addFigure(new Planelike(a, b, c));
    }
    return std::make_pair(camera, scene);
}

std::pair<Camera, Scene> Reader::readRt(const std::string &filename) const {
    Scene scene;
    Camera camera;

    std::ifstream fin(filename);

    // Reading viewport
    {
        std::string s;
        fin >> s;
        assert(s == "viewport");
        fin >> s >> camera.origin;
        assert(s == "origin");
        fin >> s >> camera.topLeft;
        assert(s == "topleft");
        fin >> s >> camera.bottomLeft;
        assert(s == "bottomleft");
        fin >> s >> camera.topRight;
        assert(s == "topright");
        fin >> s;
        assert(s == "endviewport");
    }

    //Reading material
    std::map<std::string, Traits> materials;
    {
        std::string s, name, textureFile;
        RGB rgb;
        real reflectionRate, refractionRate, refractiveId;

        fin >> s;
        assert(s == "materials");
        fin >> s;
        while (s == "entry") {
            fin >> s >> name;
            assert(s == "name");
            fin >> s;
            if (s == "color") {
                fin >> rgb;

            }
            else {
                assert(s == "texture");
                fin >> textureFile;
            }
            fin >> s >> reflectionRate;
            assert(s == "reflect");
            fin >> s >> refractionRate;
            assert(s == "refract");
            fin >> s >> refractiveId;
            assert(s == "refractId");
            fin >> s;
            assert(s == "endentry");
            materials[name] = Traits(rgb.toColor(), reflectionRate, refractionRate, refractiveId);;
            fin >> s;
        }
        assert(s == "endmaterials");
    }


    //Reading Lights
    {
        std::string s;
        real p, p2, d;
        Vec3d v;

        fin >> s;
        assert(s == "lights");

        fin >> s;
        assert(s == "reference");
        fin >> s >> settings.lightNormalPower;
        assert(s == "power");
        fin >> s >> settings.lightNormalDistance;
        assert(s == "distance");
        fin >> s;
        assert(s == "endreference");

        fin >> s;
        while (s == "point") {
            fin >> s >> v;
            assert(s == "coords");
            fin >> s >> p2;
            assert(s == "power");
            fin >> s;
            assert(s == "endpoint");

            scene.addLight(LightSource(v, p2));

            fin >> s;
        }
        assert(s == "endlights");
    }

    //Reading Figures
    {
        std::string s, materialId;
        real r;
        Vec3d v1, v2, v3, v4;
        Figure3d *figure = nullptr;

        fin >> s;
        assert(s == "geometry");

        fin >> s;
        while (s != "endgeometry") {
            assert(s == "sphere"
                   || s == "triangle"
                   || s == "plane"
                   || s == "plane3v"
                   || s == "quadrangle");
            if (s == "sphere") {
                fin >> s >> v1;
                assert(s == "coords");
                fin >> s >> r;
                assert(s == "radius");
                fin >> s >> materialId;
                assert(s == "material");
                fin >> s;
                assert(s == "endsphere");
                figure = new Sphere(v1, r);
            }
            else if (s == "plane") {
                fin >> s >> v1;
                assert(s == "loc");
                fin >> s >> v2;
                assert(s == "normal");
                fin >> s >> materialId;
                assert(s == "material");
                fin >> s;
                assert(s == "endplane");
                figure = new Plane(v2, v1);
            }
            else if (s == "plane3v") {
                fin >> s >> v1;
                assert(s == "vertex");
                fin >> s >> v2;
                assert(s == "vertex");
                fin >> s >> v3;
                assert(s == "vertex");
                fin >> s >> materialId;
                assert(s == "material");
                fin >> s;
                assert(s == "endplane3v");
                figure = new Plane((v2 - v1) ^ (v3 - v1), v1);
            }
            else if (s == "triangle") {
                fin >> s >> v1;
                assert(s == "vertex");
                fin >> s >> v2;
                assert(s == "vertex");
                fin >> s >> v3;
                assert(s == "vertex");
                fin >> s >> materialId;
                assert(s == "material");
                fin >> s;
                assert(s == "endtriangle");
                figure = new Planelike(v1, v2, v3);
            }
            else if (s == "quadrangle") {
                fin >> s >> v1;
                assert(s == "vertex");
                fin >> s >> v2;
                assert(s == "vertex");
                fin >> s >> v3;
                assert(s == "vertex");
                fin >> s >> v4;
                assert(s == "vertex");
                fin >> s >> materialId;
                assert(s == "material");
                fin >> s;
                assert(s == "endquadrangle");
                figure = new Planelike(v1, v2, v3, v4);
            }

            figure->traits = materials[materialId];
            scene.addFigure(figure);
            fin >> s;
        }
        assert(s == "endgeometry");
    }




    return std::make_pair(camera, scene);
}

std::pair<Camera, Scene> Reader::read(const std::string &filename) const {
    if (filename.back() == 'l') {
        return readStl(filename);
    }
    else if (filename.back() == 't') {
        return readRt(filename);
    }
    throw "FUUUUCK!";
}





