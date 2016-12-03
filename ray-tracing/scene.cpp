#include <iostream>

#include "scene.h"

void Scene::addFigure(Figure3d *figure) {
    figures.push_back(figure);
}

void Scene::addLight(LightSource light) {
    lights.push_back(light);
}

