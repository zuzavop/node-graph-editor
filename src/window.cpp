#include "window.h"

Window::Window(int width, int height)
    : m_window(nullptr), m_renderer(nullptr), m_width(width), m_height(height),
      m_running(false), m_fullScreen(false), m_shown(false) {}

bool Window::init(const char *name, int width, int height, bool isResizable,
                  bool isShown) {
  // set texture filtering to linear
  if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
    std::cerr << "Warning: Linear texture filtering not enabled!" << std::endl;
  }

  // create a window
  m_window = SDL_CreateWindow(
      name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height,
      isResizable && isShown
          ? SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
          : (isShown ? SDL_WINDOW_SHOWN
                     : (isResizable ? SDL_WINDOW_RESIZABLE : 0)));

  if (!m_window) {
    std::cout << "Failed to create window: " << SDL_GetError() << std::endl;
    return false;
  } else {
    m_width = width;
    m_height = height;
  }

  // create a renderer
  m_renderer = SDL_CreateRenderer(
      m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  if (!m_renderer) {
    std::cout << "Failed to create renderer: " << SDL_GetError() << std::endl;
    return false;
  }

  m_id = SDL_GetWindowID(m_window);
  m_running = true;
  m_shown = true;

  return true;
}

void Window::focus() {
  if (!m_shown) {
    SDL_ShowWindow(m_window);
    m_shown = true;
  }

  SDL_RaiseWindow(m_window);
}
