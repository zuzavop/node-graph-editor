#include "main_window.h"

int main(int argc, char* argv[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
	std::cerr << "SDL could not initialize! SDL Error:" << SDL_GetError() << std::endl;
	return 1;
    }
    
    MainWindow main_window;

    if (main_window.createWindow()) {
        main_window.mainLoop();
    } else {
        return 1;
    }

    return 0;
}
