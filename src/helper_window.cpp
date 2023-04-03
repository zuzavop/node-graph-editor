#include "helper_window.h"

HelperWindow::HelperWindow() : Window() {}

HelperWindow::~HelperWindow() {
  SDL_DestroyWindow(_window);
  SDL_DestroyRenderer(_renderer);
}

bool HelperWindow::init() { return Window::init(); }

void HelperWindow::mainLoop() {
  while (_running) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        _running = false;
      }
    }
    renderWindow();
  }
}

void HelperWindow::renderWindow() {
  // clear the screen
  SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
  SDL_RenderClear(_renderer);

  // present the renderer
  SDL_RenderPresent(_renderer);
}
