//
// Created by manatee on 09.05.16.
//

#ifndef GRAPHIC3D_STLREADER_H
#define GRAPHIC3D_STLREADER_H

#include <cstring>
#include <vector>
#include "../scene.h"
#include "../camera.h"

class Reader {
private:
    std::pair<Camera, Scene> readStl(const std::string &filename) const;
    std::pair<Camera, Scene> readRt(const std::string &filename) const;
public:
    Reader();
    std::pair<Camera, Scene> read(const std::string &filename) const;
};

const Reader defaultReader;

#endif //GRAPHIC3D_STLREADER_H
