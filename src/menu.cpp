#include "menu.h"
#include "command.h"
#include "main_window.h"

void MenuBar::init(std::shared_ptr<MainWindow> window) {
  float scale = 0.7;
  _buttons.push_back(std::make_unique<Button>(
      std::make_shared<NewCommand>(window), _font, "New", scale));
  _buttons.push_back(std::make_unique<Button>(
      std::make_shared<SaveCommand>(window), _font, "Save", scale));
  _buttons.push_back(std::make_unique<Button>(
      std::make_shared<LoadCommand>(window), _font, "Open", scale));
  _buttons.push_back(std::make_unique<Button>(
      std::make_shared<ExportCommand>(window), _font, "Export", scale));
  _buttons.push_back(std::make_unique<Button>(
      std::make_shared<LayoutCommand>(window), _font, "Layout", scale));

  int startX = 0;
  for (std::size_t i = 0; i < _buttons.size(); ++i) {
    _buttons[i]->setPosition(startX, 0);
    startX += _buttons[i]->getWidth() * scale + 10;
    _height = _buttons[i]->getHeight() * scale > _height
                  ? _buttons[i]->getHeight() * scale
                  : _height;
  }
}

void MenuBar::handleEvent(SDL_Event *event) {
  for (std::size_t i = 0; i < _buttons.size(); ++i) {
    _buttons[i]->handleEvent(event);
  }
}

void MenuBar::draw(SDL_Renderer *renderer) {
  for (std::size_t i = 0; i < _buttons.size(); ++i) {
    _buttons[i]->render(renderer);
  }
}

bool MenuBar::clickedInMenu(int x, int y) {
  if (y < _height) {
    return true;
  }
  return false;
}
