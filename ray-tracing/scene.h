#ifndef _SCENE_H_
#define _SCENE_H_

#include "containers/figurelist.h"
#include "lights/lightsource.h"

class Scene {
public:
    FigureList figures;
    std::vector<LightSource> lights;

    void addFigure(Figure3d* figure);
    void addLight(LightSource light);
};

#endif // _SCENE_H_