#ifndef WINDOW_H_
#define WINDOW_H_

#include <SDL2/SDL.h>
#include "graph.h"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

class MainWindow {
    public:
        MainWindow();
        void create_window();
        void main_loop();
        void close_window();

    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
        Graph graph;
        void render_window();
}

#endif