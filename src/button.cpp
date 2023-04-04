#include "button.h"

Button::Button(Command &c, std::shared_ptr<BitmapFont> f) : _function(c), _font(f) {
  _position.x = 0;
  _position.y = 0;

  _width = BUTTON_WIDTH;
  _height = BUTTON_HEIGHT;

  _sprite = BUTTON_SPRITE_MOUSE_OUT;
}

void Button::setPosition(int x, int y) {
  _position.x = x;
  _position.y = y;
}

void Button::setSize(int w, int h) {
  _width = w;
  _height = h;
}

void Button::handleEvent(SDL_Event *e) {
  if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN ||
      e->type == SDL_MOUSEBUTTONUP) {
    int x, y;
    SDL_GetMouseState(&x, &y); // mouse position

    // check if mouse is in button
    bool inside = true;
    if (x < _position.x || x > _position.x + BUTTON_WIDTH || y < _position.y ||
        y > _position.y + BUTTON_HEIGHT) {
      inside = false;
    }

    if (!inside) {
      _sprite = BUTTON_SPRITE_MOUSE_OUT;
    } else {
      // set mouse over sprite
      switch (e->type) {
      case SDL_MOUSEMOTION:
        _sprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
        break;

      case SDL_MOUSEBUTTONDOWN:
        _function.execute();
        _sprite = BUTTON_SPRITE_MOUSE_DOWN;
        break;

      case SDL_MOUSEBUTTONUP:
        _sprite = BUTTON_SPRITE_MOUSE_UP;
        break;
      }
    }
  }
}

void Button::render(SDL_Rect *clip, SDL_Renderer *renderer,
                    SDL_Texture *texture) {
  // set rendering space
  SDL_Rect renderQuad = {_position.x, _position.y, 0, 0};

  if (clip != NULL) {
    renderQuad.w = clip->w;
    renderQuad.h = clip->h;
  }

  // render to screen
  SDL_RenderCopyEx(renderer, texture, clip, &renderQuad, 0.0, NULL,
                   SDL_FLIP_NONE);
}
