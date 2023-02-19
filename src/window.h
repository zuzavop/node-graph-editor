#include <SDL2/SDL.h>

#ifndef WINDOW_H_
#define WINDOW_H_

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int NODE_RADIUS = 20;

// Define a structure for a graph node
struct Node {
    int x, y;
};

// Define a structure for a graph edge
struct Edge {
    int start, end;
};

class MainWindow {
    public:
        MainWindow();
        ~MainWindow();
        createWindow();
        mainLoop();

    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
}

#endif