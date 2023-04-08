#ifndef BUTTON_H
#define BUTTON_H

#include "command.h"
#include "text.h"

// button constants
const int BUTTON_WIDTH = 300;
const int BUTTON_HEIGHT = 200;

class Button {
public:
  Button(std::shared_ptr<Command> function, std::shared_ptr<BitmapFont> font,
         std::string name, float scale = NORMAL_FONT_SCALE);

  void setPosition(int x, int y); // sets top left position
  void setSize(int w, int h);
  void setTitle(const std::string &name);

  int getWidth() const { return m_width * m_scale; }
  int getHeight() const { return m_height * m_scale; }
  const std::shared_ptr<Command> getFunction() const { return m_function; }

  void handleEvent(SDL_Event &event);
  void render(SDL_Renderer *renderer);

private:
  SDL_Point m_position;
  int m_width, m_height;
  std::string m_title;

  std::shared_ptr<Command> m_function;
  std::shared_ptr<BitmapFont> m_font;
  float m_scale;
};

#endif
