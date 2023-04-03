#ifndef BUTTON_H
#define BUTTON_H

#include <SDL2/SDL.h>

#include "command.h"

// button constants
const int BUTTON_WIDTH = 300;
const int BUTTON_HEIGHT = 200;

enum ButtonSprite {
  BUTTON_SPRITE_MOUSE_OUT = 0,
  BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
  BUTTON_SPRITE_MOUSE_DOWN = 2,
  BUTTON_SPRITE_MOUSE_UP = 3,
  BUTTON_SPRITE_TOTAL = 4
};

class Button {
public:
  Button(Command &f);
  
  void setPosition(int x, int y); // sets top left position
  void handleEvent(SDL_Event *e);
  void render(SDL_Rect *clip, SDL_Renderer *renderer, SDL_Texture *texture);

private:
  SDL_Point mPosition;
  ButtonSprite mCurrentSprite;
  Command &function;
};

#endif
