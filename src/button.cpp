#include "button.h"
#include "command.h"
#include "main_window.h"

Button::Button(std::unique_ptr<Command> f, std::string name, double scale)
    : function(std::move(f)), m_title(name) {
  m_position.x = 0;
  m_position.y = 0;
  m_scale = scale;

  m_width = MainWindow::getInstance().font->getWordWidth(name);
  if (m_width == 0) {
    m_width = BUTTON_WIDTH;
  }
  m_height = MainWindow::getInstance().font->getWordHeight(name);
  if (m_height == 0) {
    m_height = BUTTON_HEIGHT;
  }
}

void Button::setPosition(int x, int y) {
  m_position.x = x;
  m_position.y = y;
}

void Button::setSize(int w, int h) {
  m_width = w;
  m_height = h;
}

void Button::setTitle(const std::string &name) {
  m_title = name;
  m_width = MainWindow::getInstance().font->getWordWidth(name);
  m_height = MainWindow::getInstance().font->getWordHeight(name);
}

void Button::handleEvent(SDL_Event &event) {
  if (event.type == SDL_MOUSEMOTION || event.type == SDL_MOUSEBUTTONDOWN ||
      event.type == SDL_MOUSEBUTTONUP) {
    int x, y;
    SDL_GetMouseState(&x, &y); // mouse position

    // check if mouse is in button
    if (x > m_position.x && x < m_position.x + getWidth() && y > m_position.y &&
        y < m_position.y + getHeight()) {
      if (event.type == SDL_MOUSEBUTTONDOWN) {
        if (function) function->execute();
      }
    }
  }
}

void Button::render(SDL_Renderer *renderer) {
  MainWindow::getInstance().font->renderText(m_position.x, m_position.y, m_title, renderer, m_scale,
                     m_width, m_height);
}

void Button::render(SDL_Renderer *renderer, std::unique_ptr<BitmapFont> &font) {
  font->renderText(m_position.x, m_position.y, m_title, renderer, m_scale,
                     m_width, m_height);
}
