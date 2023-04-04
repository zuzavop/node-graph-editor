#ifndef MENU_H
#define MENU_H

#include <SDL2/SDL.h>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "button.h"
#include "text.h"

class MainWindow;

class MenuBar {
public:
  MenuBar(std::shared_ptr<BitmapFont> f) : _font(f){};
  ~MenuBar(){};

  void init(std::shared_ptr<MainWindow> window);
  void handleEvent(SDL_Event *event);
  void draw(SDL_Renderer *r);
  bool clickedInMenu(int x, int y);
  int getHeight() { return _height; }

private:
  std::shared_ptr<BitmapFont> _font;
  std::vector<std::unique_ptr<Button>> _buttons;

  int _height;
};

#endif
