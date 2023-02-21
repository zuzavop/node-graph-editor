#include "window.h"

MainWindow::MainWindow() {
    // Initialize SDL
    SDL_Init(SDL_INIT_VIDEO);
}

MainWindow::close_window() {
    // Clean up and exit
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

MainWindow::create_window() {
    // Create a window
    window = SDL_CreateWindow("Graph Editor", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);

    // Create a renderer
    renderer = SDL_CreateRenderer(window, -1, 0);
}

MainWindow::main_loop() {
    // Initialize the graph
    Graph graph;

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
                        graph.add_node(event.button.x, event.button.y);
                    }
                    // Handle edge creation
                    else if (event.button.button == SDL_BUTTON_RIGHT) {
                        graph.add_edge(event.button.x, event.button.y);
                    }
                    break;
                case SDL_KEYDOWN:
                    // Handle edge deletion
                    if (event.key.keysym.sym == SDLK_BACKSPACE) {
                        graph.delete_edge();
                    }
                    break;
            }
        }

        // Clear the renderer
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        // Draw the edges
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        for (const Edge& edge : graph.edges) {
            int startX = graph.nodes[edge.start].x;
            int startY = graph.nodes[edge.start].y;
            int endX = graph.nodes[edge.end].x;
            int endY = graph.nodes[edge.end].y;
            SDL_RenderDrawLine(renderer, startX, startY, endX, endY);
        }

        // Draw the nodes
        for (const Node& node : graph.nodes) {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderDrawCircle(renderer, node.x, node.y, NODE_RADIUS);
        }

        // Present the renderer
        SDL_RenderPresent(renderer);
    }
    close_window();
}