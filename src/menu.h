#ifndef MENU_H
#define MENU_H

#include <SDL2/SDL.h>
#include <iostream>
#include <string>

class MenuBar {
public:
  MenuBar(){};
  ~MenuBar();
  bool init(SDL_Renderer *renderer);
  void handleEvent(SDL_Event event);
  void draw();

private:
  SDL_Renderer *renderer;
  bool fileButtonSelected;
  SDL_Surface *fontSurface;
  SDL_Texture *fontTexture;
};

#endif
