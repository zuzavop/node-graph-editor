#include "main_window.h"

int main(int argc, char *argv[]) {
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    std::cerr << "SDL could not initialize! SDL Error:" << SDL_GetError()
              << std::endl;
    return 1;
  }

  if (MainWindow::getInstance().init("Graph Editor")) {
    MainWindow::getInstance().mainLoop();
  } else {
    return 1;
  }

  return 0;
}
