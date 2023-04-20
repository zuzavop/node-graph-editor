#ifndef BUTTON_H
#define BUTTON_H

#include <memory>

#include "text.h"
#include "command.h"

// button constants
const int BUTTON_WIDTH = 300;
const int BUTTON_HEIGHT = 200;

class Button {
public:
  Button(std::unique_ptr<Command> f, std::string name, double scale = NORMAL_FONT_SCALE);

  void setPosition(int x, int y); // sets top left position
  void setSize(int w, int h);
  void setTitle(const std::string &name);

  double getWidth() const { return m_width * m_scale; }
  double getHeight() const { return m_height * m_scale; }

  void handleEvent(SDL_Event &event);
  void render(SDL_Renderer *renderer);
  void render(SDL_Renderer *renderer, std::unique_ptr<BitmapFont> &font);

  const std::unique_ptr<Command> function;

private:
  double m_scale;
  SDL_Point m_position;
  int m_width, m_height;
  std::string m_title;
};

#endif
