#ifndef WINDOW_H_
#define WINDOW_H_

#include "graph.h"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

class MainWindow {
    public:
        MainWindow();
        ~MainWindow();
        void createWindow();
        void mainLoop();

    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
        Graph graph;
        void renderWindow();
        std::shared_ptr<Node> selectedNode;
        std::shared_ptr<Edge> selectedEdge;
        void handleEvents();
        bool running;
        bool dragging;
};

#endif