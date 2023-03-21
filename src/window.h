#ifndef WINDOW_H_
#define WINDOW_H_

#include "graph.h"
#include "menu.h"

int WINDOW_WIDTH = 800;
int WINDOW_HEIGHT = 600;

class MainWindow {
    public:
        MainWindow();
        ~MainWindow();
        bool createWindow();
        void mainLoop();

    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
        Graph graph;
        MenuBar menuBar;
        void renderWindow();
        std::shared_ptr<Node> startNode;
        std::shared_ptr<Edge> selectedEdge;
        void handleEvents();
        bool running;
        bool dragging;
};

#endif
