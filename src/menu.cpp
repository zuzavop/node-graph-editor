#include "menu.h"
#include "command.h"
#include "window.h"

void MenuBar::init() {
  addMenuButton(std::make_unique<NewCommand>(), "New");
  addMenuButton(std::make_unique<SaveCommand>(), "Save");
  addMenuButton(std::make_unique<LoadCommand>(), "Open");
  addMenuButton(std::make_unique<ExportCommand>(), "Export");
  addMenuButton(std::make_unique<LayoutCommand>(), "Layout");

  layoutButtons();
}

void MenuBar::addMenuButton(std::unique_ptr<Command> command,
                            const std::string& label) {
  m_buttons.push_back(std::make_unique<Button>(std::move(command), label, BIG_FONT_SCALE));
}

void MenuBar::layoutButtons() {
  int startX = 0;
  for (std::size_t i = 0; i < m_buttons.size(); ++i) {
    m_buttons[i]->setPosition(startX, 0);
    startX += (int)(m_buttons[i]->getWidth() + PADDING);
    m_height = std::max<int>(m_height, (int)m_buttons[i]->getHeight());
  }
  m_width = startX - PADDING;
}

void MenuBar::handleEvent(SDL_Event &event) {
  for (std::size_t i = 0; i < m_buttons.size(); ++i) {
    m_buttons[i]->handleEvent(event);
  }
}

void MenuBar::draw(SDL_Renderer *renderer) {
  for (std::size_t i = 0; i < m_buttons.size(); ++i) {
    m_buttons[i]->render(renderer);
  }
}

bool MenuBar::clickedInMenu(int x, int y) {
  return y < m_height + WINDOW_PADDING && x < m_width + WINDOW_PADDING && x > 0 && y > 0;
}
