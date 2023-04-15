#include "window.h"

Window::Window(int width, int height)
    : m_window(nullptr), m_renderer(nullptr), m_width(width), m_height(height),
      m_fullScreen(false), m_running(false), m_shown(false) {}

bool Window::init(const char *name, int width, int height, bool isResizable,
                  bool isShown) {
  // set texture filtering to linear
  if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
    std::cerr << "Warning: Linear texture filtering not enabled!" << std::endl;
    return false;
  }

  // Create a window with specified parameters
  Uint32 windowFlags = SDL_WINDOW_SHOWN;
  if (isResizable) windowFlags |= SDL_WINDOW_RESIZABLE;
  if (isShown) windowFlags |= SDL_WINDOW_SHOWN;

  // create a window
  m_window = SDL_CreateWindow(
      name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, windowFlags);

  if (!m_window) {
    std::cout << "Failed to create window: " << SDL_GetError() << std::endl;
    return false;
  } 
    
  m_width = width;
  m_height = height;

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
