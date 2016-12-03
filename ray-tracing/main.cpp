#include <iostream>
#include "screen/screen.h"
#include "camera.h"
#include "reader/reader.h"
#include "settings.h"


using namespace std;

int main(int argc, char** argv) {
    auto cs = defaultReader.read("tests/refraction.rt");

    Camera camera = cs.first;
    camera.setScreenSize(settings);

    Scene scene = cs.second;
    ScreenBuffer screenBuffer = initScreen(settings);
    camera.shot(scene, screenBuffer, true);

    genPng(screenBuffer);

    return 0;
}
