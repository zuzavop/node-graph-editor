#include "main_window.h"

int main(int argc, char *argv[]) {
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    std::cerr << "SDL could not initialize! SDL Error:" << SDL_GetError()
              << std::endl;
    return 1;
  }

  std::shared_ptr<MainWindow> main_window(new MainWindow);

  if (main_window->init("Graph Editor")) {
    main_window->mainLoop();
  } else {
    return 1;
  }

  return 0;
}
