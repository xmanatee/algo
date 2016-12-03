#ifndef _SCREEN_H_
#define _SCREEN_H_

#include <vector>
#include <ostream>
#include "rgb.h"
#include "../settings.h"

typedef std::vector<std::vector<RGB>> ScreenBuffer;

ScreenBuffer initScreen(const Settings& settings);

std::ostream& operator << (std::ostream& out, const ScreenBuffer& screen);

void genPng(const ScreenBuffer& screen);

#endif // _SCREEN_H_
