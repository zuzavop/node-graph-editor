#include "window.h"

MainWindow::MainWindow() {
    // Initialize SDL
    SDL_Init(SDL_INIT_VIDEO);
}

void MainWindow::close_window() {
    // Clean up and exit
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void MainWindow::create_window() {
    // Create a window
    window = SDL_CreateWindow("Graph Editor", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);

    // Create a renderer
    renderer = SDL_CreateRenderer(window, -1, 0);

    // create a graph
    Graph graph = new Graph();
}

void MainWindow::main_loop() {
    // Loop to handle events
    SDL_Event event;
    bool running = true;
    bool dragging = false;
    Node* startNode = nullptr;
    int startX = 0, startY = 0;

    while (running) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    running = false;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    // check if the mouse was clicked on a node
                    for (auto node : graph->getNodes()) {
                        if (node->isClicked(event.button.x, event.button.y)) {
                            // handle node click
                            node->setSelected(true);
                            dragging = true;
                            startNode = node;
                            startX = event.button.x;
                            startY = event.button.y;
                        }
                    }
                    break;
                case SDL_KEYDOWN:
                    // Handle edge deletion
                    if (event.key.keysym.sym == SDLK_DELETE) {
                        // delete selected nodes and edges
                        for (auto node : graph->getNodes()) {
                            if (node->isSelected()) {
                                graph->removeNode(node);
                            }
                        }
                        for (auto edge : graph->getEdges()) {
                            if (edge->isSelected()) {
                                graph->removeEdge(edge);
                            }
                        }
                    }
                    break;
                case SDL_MOUSEBUTTONUP:
                    // clear node selection
                    for (auto node : graph->getNodes()) {
                        node->setSelected(false);
                    }
                    if (dragging) {
                        // check if the mouse was released on a node
                        bool releasedOnNode = false;
                        for (auto node : graph->getNodes()) {
                            if (node->isClicked(event.button.x, event.button.y)) {
                                // handle node release
                                if (startNode != node) {
                                    graph->addEdge(new Edge(startNode, node));
                                }
                                releasedOnNode = true;
                                break;
                            }
                        }
                        if (!releasedOnNode) {
                            // handle canvas release
                            graph->addNode(new Node(event.button.x, event.button.y));
                        }
                        dragging = false;
                    }
                    break;
                case SDL_MOUSEMOTION:
                    // move selected nodes or handle drag
                    if (dragging) {
                        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                        SDL_RenderDrawLine(renderer, startX, startY, event.motion.x, event.motion.y);
                    }
                    else {
                        for (auto node : graph->getNodes()) {
                            if (node->isSelected()) {
                                node->move(event.motion.xrel, event.motion.yrel);
                            }
                        }
                    }
                    break;
                default:
                    break;
            }
        }

        render_window();
    }
    close_window();
}

void MainWindow::render_window() {
    // clear the screen
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    // draw the graph
    graph->draw(renderer);

    // present the renderer
    SDL_RenderPresent(renderer);
}

void MainWindow::renderText(SDL_Renderer* renderer) {
    TTF_Font* font = TTF_OpenFont("arial.ttf", 16);
    SDL_Color color = { 0, 0, 0, 255 };
    for (auto node : nodes) {
        SDL_Surface* surface = TTF_RenderText_Solid(font, std::to_string(node->getID()).c_str(), color);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_Rect rect = { node->getX(), node->getY() - 20, surface->w, surface->h };
        SDL_RenderCopy(renderer, texture, NULL, &rect);
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
    }
    TTF_CloseFont(font);
}