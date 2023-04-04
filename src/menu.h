#ifndef MENU_H
#define MENU_H

#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include <memory>
#include <vector>

#include "text.h"
#include "button.h"

class MenuBar {
public:
  MenuBar(std::shared_ptr<BitmapFont> f) : font(f) {};
  ~MenuBar() {};

  void init();
  void handleEvent(SDL_Event event);
  void draw(SDL_Renderer *r);

private:
  std::shared_ptr<BitmapFont> font;
  bool fileButtonSelected;
};

#endif
