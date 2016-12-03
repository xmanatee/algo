//
// Created by manatee on 12.05.16.
//

#ifndef GRAPHIC3D_SETTINGS_H_H
#define GRAPHIC3D_SETTINGS_H_H

#include <string>

#include "utils/numeric.h"

class Settings {
public:
    int screenWidth = 1000;
    int screenHeight = 1000;

    small tracingDepth = 6;
    int verbose = 0;

    Settings() {}


    real lightNormalDistance = 1;
    real lightNormalPower = 1;

    real threadNumber = 4;
};

extern Settings settings;
#endif //GRAPHIC3D_SETTINGS_H_H
