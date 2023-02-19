#include "window.hpp"

MainWindow::MainWindow() {
    // Initialize SDL
    SDL_Init(SDL_INIT_VIDEO);
}

MainWindow::~MainWindow() {
    // Clean up and exit
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

MainWindow::createWindow() {
    // Create a window
    window = SDL_CreateWindow("Graph Editor", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);

    // Create a renderer
    renderer = SDL_CreateRenderer(window, -1, 0);
}

MainWindow::mainLoop() {
    // Initialize the graph with two nodes and no edges
    std::vector<Node> nodes = {{100, 100}, {200, 200}};
    std::vector<Edge> edges;

    // Loop to handle events
    bool running = true;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    running = false;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    // Handle node creation
                    if (event.button.button == SDL_BUTTON_LEFT) {
                        int mouseX = event.button.x;
                        int mouseY = event.button.y;
                        nodes.push_back({mouseX, mouseY});
                    }
                    // Handle edge creation
                    else if (event.button.button == SDL_BUTTON_RIGHT) {
                        int mouseX = event.button.x;
                        int mouseY = event.button.y;
                        for (int i = 0; i < nodes.size(); i++) {
                            int nodeX = nodes[i].x;
                            int nodeY = nodes[i].y;
                            int dx = mouseX - nodeX;
                            int dy = mouseY - nodeY;
                            if (dx * dx + dy * dy < NODE_RADIUS * NODE_RADIUS) {
                                if (edges.empty()) {
                                    edges.push_back({i, i});
                                } else {
                                    edges.back().end = i;
                                }
                                break;
                            }
                        }
                    }
                    break;
                case SDL_KEYDOWN:
                    // Handle edge deletion
                    if (event.key.keysym.sym == SDLK_BACKSPACE && !edges.empty()) {
                        edges.pop_back();
                    }
                    break;
            }
        }

        // Clear the renderer
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        // Draw the edges
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        for (const Edge& edge : edges) {
            int startX = nodes[edge.start].x;
            int startY = nodes[edge.start].y;
            int endX = nodes[edge.end].x;
            int endY = nodes[edge.end].y;
            SDL_RenderDrawLine(renderer, startX, startY, endX, endY);
        }

        // Draw the nodes
        for (const Node& node : nodes) {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderDrawCircle(renderer, node.x, node.y, NODE_RADIUS);
        }

        // Present the renderer
        SDL_RenderPresent(renderer);
    }
}