#include "window.h"

Window::Window(int width, int height)
    : _window(nullptr), _renderer(nullptr), _width(width), _height(height),
      _running(true), _mouseFocus(false), _keyboardFocus(false),
      _fullScreen(false), _minimized(false) {}

bool Window::init(const char* name) {
  // set texture filtering to linear
  if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
    std::cerr << "Warning: Linear texture filtering not enabled!" << std::endl;
  }

  // create a window
  _window = SDL_CreateWindow(
      name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH,
      WINDOW_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

  if (!_window) {
    std::cout << "Failed to create window: " << SDL_GetError() << std::endl;
    return false;
  } else {
    _mouseFocus = true;
    _keyboardFocus = true;
    _width = WINDOW_WIDTH;
    _height = WINDOW_HEIGHT;
  }

  // create a renderer
  _renderer = SDL_CreateRenderer(
      _window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  if (!_renderer) {
    std::cout << "Failed to create renderer: " << SDL_GetError() << std::endl;
    return false;
  }

  return true;
}
