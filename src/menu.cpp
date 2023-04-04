#include "menu.h"
#include "command.h"
#include "main_window.h"

void MenuBar::init(std::shared_ptr<MainWindow> window) {
  _buttons.push_back(std::make_unique<Button>(
      std::make_unique<SaveCommand>(window), _font, "Save"));
  _buttons.push_back(std::make_unique<Button>(
      std::make_unique<LoadCommand>(window), _font, "Load"));
  _buttons.push_back(std::make_unique<Button>(
      std::make_unique<ExportCommand>(window), _font, "Export"));
  _buttons.push_back(std::make_unique<Button>(
      std::make_unique<LayoutCommand>(window), _font, "Layout"));

  int startX = 0;
  for (std::size_t i = 0; i < _buttons.size(); ++i) {
    _buttons[i]->setPosition(startX, 0);
    startX += _buttons[i]->getWidth() + 10;
  }
  _height = _buttons[0]->getHeight();
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
