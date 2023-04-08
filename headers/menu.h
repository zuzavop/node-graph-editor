#ifndef MENU_H
#define MENU_H

#include "button.h"
#include "command.h"

class MainWindow;

class MenuBar {
public:
  MenuBar(std::shared_ptr<BitmapFont> font) : m_font(font), m_height(0), m_width(0) {};
  ~MenuBar(){};

  void init(std::shared_ptr<MainWindow> window);
  void handleEvent(SDL_Event &event);
  void draw(SDL_Renderer *r);
  bool clickedInMenu(int x, int y);

  int getHeight() const { return m_height; }

private:
  std::shared_ptr<BitmapFont> m_font;
  std::vector<std::unique_ptr<Button>> m_buttons;
  int m_height, m_width;
};

#endif
