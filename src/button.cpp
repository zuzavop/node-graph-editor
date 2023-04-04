#include "button.h"

Button::Button(std::unique_ptr<Command> c, std::shared_ptr<BitmapFont> f,
               const std::string &name)
    : _function(std::move(c)), _font(f), _title(name) {
  _position.x = 0;
  _position.y = 0;

  _width = _font->getWordWidth(name);
  if (_width == 0) {
    _width = BUTTON_WIDTH;
  }
  _height = _font->getWordHeight(name);
  if (_height == 0) {
	  _height = BUTTON_HEIGHT;
  }
}

void Button::setPosition(int x, int y) {
  _position.x = x;
  _position.y = y;
}

void Button::setSize(int w, int h) {
  _width = w;
  _height = h;
}

void Button::setTitle(const std::string &name) {
  _title = name;
  _width = _font->getWordWidth(name);
  _height = _font->getWordHeight(name);
}

void Button::handleEvent(SDL_Event *e) {
  if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN ||
      e->type == SDL_MOUSEBUTTONUP) {
    int x, y;
    SDL_GetMouseState(&x, &y); // mouse position

    // check if mouse is in button
    if (x > _position.x && x < _position.x + _width && y > _position.y &&
        y < _position.y + _height) {
      if (e->type == SDL_MOUSEBUTTONDOWN) {
        _function->execute();
      }
    }
  }
}

void Button::render(SDL_Renderer *renderer) {
  const SDL_Rect buttonSpace = {_position.x, _position.y, _width, _height};
  SDL_RenderFillRect(renderer, &buttonSpace);

  _font->renderText(_position.x, _position.y, _title, renderer);
}
