#ifndef COLORS_H
#define COLORS_H

#ifndef _MSC_VER
#include <SDL2/SDL.h>
#else
#include "SDL.h"
#endif

const SDL_Color WHITE = {255, 255, 255, 255};
const SDL_Color BLACK = {0, 0, 0, 255};
const SDL_Color RED = {255, 0, 0, 255};
const SDL_Color GREEN = {0, 255, 0, 255};
const SDL_Color BLUE = {0, 0, 255, 255};

#endif
