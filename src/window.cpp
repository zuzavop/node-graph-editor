#include "window.h"

Window::Window(int width, int height)
    : _window(nullptr), _renderer(nullptr), _width(width), _height(height),
      _running(false), _fullScreen(false), _shown(false) {}

bool Window::init(const char *name, int width, int height) {
  // set texture filtering to linear
  if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
    std::cerr << "Warning: Linear texture filtering not enabled!" << std::endl;
  }

  // create a window
  _window =
      SDL_CreateWindow(name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

  if (!_window) {
    std::cout << "Failed to create window: " << SDL_GetError() << std::endl;
    return false;
  } else {
    _width = width;
    _height = height;
  }

  // create a renderer
  _renderer = SDL_CreateRenderer(
      _window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  if (!_renderer) {
    std::cout << "Failed to create renderer: " << SDL_GetError() << std::endl;
    return false;
  }

  _id = SDL_GetWindowID(_window);
  _running = true;
  _shown = true;

  return true;
}

void Window::focus() {
  if (!_shown) {
    SDL_ShowWindow(_window);
    _shown = true;
  }

  SDL_RaiseWindow(_window);
}
