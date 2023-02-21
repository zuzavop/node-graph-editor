#include <SDL2/SDL.h>
#include "graph.h"

#ifndef WINDOW_H_
#define WINDOW_H_

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

class MainWindow {
    public:
        MainWindow();
        create_window();
        main_loop();
        close_window();

    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
}

#endif