#include "window.h"

MainWindow::MainWindow() : menuBar(renderer) {
    // Initialize SDL
    SDL_Init(SDL_INIT_VIDEO);
    running = true;
    dragging = false;
}

MainWindow::~MainWindow() {
    // Clean up and exit
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void MainWindow::createWindow() {
    // Create a window
    window = SDL_CreateWindow("Graph Editor", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

    // Create a renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

void MainWindow::mainLoop() {
    // Loop to handle events
    while (running) {
        handleEvents();

        renderWindow();
    }
}

void MainWindow::renderWindow() {
    // clear the screen
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    // draw the graph
    graph.draw(renderer);

    menuBar.draw();

    // present the renderer
    SDL_RenderPresent(renderer);
}

void MainWindow::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                running = false;
                break;
            case SDL_MOUSEBUTTONDOWN:
                // check if the mouse was clicked on a node
                for (auto node : graph.getNodes()) {
                    if (node->isClicked(event.button.x, event.button.y)) {
                        // handle node click
                        node->setSelected(true);
                        dragging = true;
                        // startNode = node;
                        // startX = event.button.x;
                        // startY = event.button.y;
                    }
                }
                break;
            case SDL_KEYDOWN:
                // Handle edge deletion
                if (event.key.keysym.sym == SDLK_DELETE) {
                    // delete selected nodes and edges
                    for (auto node : graph.getNodes()) {
                        if (node->isSelected()) {
                            graph.removeNode(node);
                        }
                    }
                    for (auto edge : graph.getEdges()) {
                        if (edge->isSelected()) {
                            graph.removeEdge(edge);
                        }
                    }
                }
                break;
            case SDL_MOUSEBUTTONUP:
                // clear node selection
                for (auto node : graph.getNodes()) {
                    node->setSelected(false);
                }
                if (dragging) {
                    // check if the mouse was released on a node
                    bool releasedOnNode = false;
                    for (auto node : graph.getNodes()) {
                        if (node->isClicked(event.button.x, event.button.y)) {
                            // handle node release
                            // if (startNode != node) {
                            //     graph.addEdge(startNode, node);
                            // }
                            releasedOnNode = true;
                            break;
                        }
                    }
                    if (!releasedOnNode) {
                        // handle canvas release
                        graph.addNode(event.button.x, event.button.y);
                    }
                    dragging = false;
                }
                break;
            case SDL_MOUSEMOTION:
                // move selected nodes or handle drag
                if (dragging) {
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                    // SDL_RenderDrawLine(renderer, startX, startY, event.motion.x, event.motion.y);
                }
                else {
                    for (auto node : graph.getNodes()) {
                        if (node->isSelected()) {
                            node->setPosition(event.motion.xrel, event.motion.yrel);
                        }
                    }
                }
                break;
            default:
                break;
        }
        menuBar.handleInput(event);
    }
}