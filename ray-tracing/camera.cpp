#ifndef _CAMERA_CPP_
#define _CAMERA_CPP_

#include <iostream>
#include "camera.h"
#include "beamtracer.h"

bool Camera::CameraTaskGenerator::isEmpty() {
    return (i >= width) || (j >= height);
}

TaskGenerator::Executor Camera::CameraTaskGenerator::operator () () {
    int i = this->i;
    int j = this->j;
    TaskGenerator::Executor e = [i, j, this] () {
        (*screen)[j][i] = camera->calcPixel(*scene, i, j);
    };
    inc();
//    std::cerr << "(" << i << "," << j << ") ";
    return e;
}

void Camera::CameraTaskGenerator::inc() {
    ++i;
    if (i == width) {
        i = 0;
        ++j;
    }
}



void Camera::setScreenSize(const Settings &settings) {
    setScreenSize(settings.screenHeight, settings.screenWidth);
}

void Camera::setScreenSize(int _screenHeignt, int _screenWidth) {
    screenHeight = _screenHeignt;
    screenWidth = _screenWidth;
    uniW = (topRight - topLeft) / screenWidth;
    uniH = (topLeft - bottomLeft) / screenHeight;
}

RGB Camera::calcPixel(const Scene& scene, int w_coord, int h_coord) const {
    Beam beam = make_beam(origin, bottomLeft + w_coord * uniW + h_coord * uniH);
    Light light = defaultTracer(beam, scene);
    return light2RGB(light);
}

void Camera::shot(const Scene& scene, ScreenBuffer &screenBuffer, bool parallel) const {
    if (parallel) {
        ThreadPool pool(new CameraTaskGenerator(&scene, &screenBuffer, this));
        pool.run();
        return;
    }
    for (int i = 0; i < screenWidth; ++i) {
        for (int j = 0; j < screenHeight; ++j) {
            screenBuffer[j][i] = calcPixel(scene, i, j);
        }
    }
}

RGB Camera::light2RGB(const Light &light) const {
    return RGB((small) cut(light.x, 0, small_max),
               (small) cut(light.y, 0, small_max),
               (small) cut(light.z, 0, small_max));
}

#endif // _CAMERA_CPP_