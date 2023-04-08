#include "menu.h"
#include "main_window.h"

void MenuBar::init(std::shared_ptr<MainWindow> window) {
  m_buttons.push_back(std::make_unique<Button>(
      std::make_shared<NewCommand>(window), m_font, "New", BIG_FONT_SCALE));
  m_buttons.push_back(std::make_unique<Button>(
      std::make_shared<SaveCommand>(window), m_font, "Save", BIG_FONT_SCALE));
  m_buttons.push_back(std::make_unique<Button>(
      std::make_shared<LoadCommand>(window), m_font, "Open", BIG_FONT_SCALE));
  m_buttons.push_back(
      std::make_unique<Button>(std::make_shared<ExportCommand>(window), m_font,
                               "Export", BIG_FONT_SCALE));
  m_buttons.push_back(
      std::make_unique<Button>(std::make_shared<LayoutCommand>(window), m_font,
                               "Layout", BIG_FONT_SCALE));

  int startX = 0;
  for (std::size_t i = 0; i < m_buttons.size(); ++i) {
    m_buttons[i]->setPosition(startX, 0);
    startX += m_buttons[i]->getWidth() * BIG_FONT_SCALE + PADDING;
    m_height = m_buttons[i]->getHeight() * BIG_FONT_SCALE > m_height
                   ? m_buttons[i]->getHeight() * BIG_FONT_SCALE
                   : m_height;
  }
  m_width = startX;
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
  return y < m_height && x < m_width && x > 0 && y > 0;
}
