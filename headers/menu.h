#ifndef MENU_H
#define MENU_H

#include "button.h"

class MenuBar {
public:
  MenuBar() : m_height(0), m_width(0) {};
  ~MenuBar(){};

  void init();
  void handleEvent(SDL_Event &event);
  void draw(SDL_Renderer *r);
  bool clickedInMenu(int x, int y);

  int getHeight() const { return m_height; }

private:
  std::vector<std::unique_ptr<Button>> m_buttons;
  int m_height, m_width;

  void layoutButtons();
  void addMenuButton(std::unique_ptr<Command> command, const std::string& label);
};

#endif
