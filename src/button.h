#ifndef BUTTON_H
#define BUTTON_H

#include <SDL2/SDL.h>

#include "command.h"
#include "text.h"

// button constants
const int BUTTON_WIDTH = 300;
const int BUTTON_HEIGHT = 200;

class Button {
public:
  Button(std::unique_ptr<Command> c, std::shared_ptr<BitmapFont> f,
         const std::string &name);

  void setPosition(int x, int y); // sets top left position
  void setSize(int w, int h);
  void setTitle(const std::string &name);

  int getWidth() { return _width; }
  int getHeight() { return _height; }

  void handleEvent(SDL_Event *e);
  void render(SDL_Renderer *renderer);

private:
  SDL_Point _position;
  int _width, _height;
  std::string _title;

  std::unique_ptr<Command> _function;
  std::shared_ptr<BitmapFont> _font;
};

#endif
