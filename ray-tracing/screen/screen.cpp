#ifndef _SCREEN_CPP_
#define _SCREEN_CPP_

#include <iostream>
#include "screen.h"
#include <png++/png.hpp>

std::ostream& operator << (std::ostream& out, const ScreenBuffer& screen) {
    int screenHeight = (int) screen.size();
    int screenWidth = (int) screen[0].size();
    for (int y = screenHeight - 1; y >= 0; --y) {
        for (int x = 0; x < screenWidth; ++x) {
            out << (screen[y][x].r == 0? "." : "#");
        }
        out << "\n";
    }
    return out;
}

ScreenBuffer initScreen(const Settings& settings) {
    ScreenBuffer screenBuffer(settings.screenHeight);
    for (int i = 0; i < settings.screenHeight; ++i) {
        screenBuffer[i].resize(settings.screenWidth);
    }
    return screenBuffer;
}

void genPng(const ScreenBuffer& screen) {
    size_t screenHeight = screen.size();
    size_t screenWidth = screen[0].size();
    png::image< png::rgb_pixel > image(screenWidth, screenHeight);

    for (size_t y = 0; y < image.get_height(); ++y) {
        for (size_t x = 0; x < image.get_width(); ++x) {
            image[y][x] = png::rgb_pixel((png::byte) screen[y][x].r, (png::byte) screen[y][x].g, (png::byte) screen[y][x].b);
        }
    }

    image.write("picture.png");
}


#endif // _SCREEN_CPP_
