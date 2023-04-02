#include "window.h"

MainWindow::MainWindow() : menuBar(renderer) {
    // Initialize SDL
    SDL_Init(SDL_INIT_VIDEO);
    running = true;
    dragging = false;

    std::shared_ptr<Node> a = std::make_shared<Node>(Node(150, 150));
    std::shared_ptr<Node> b = std::make_shared<Node>(Node(200, 150));
    std::shared_ptr<Node> c = std::make_shared<Node>(Node(50, 50));
    std::shared_ptr<Node> d = std::make_shared<Node>(Node(100, 100));
    std::shared_ptr<Node> e = std::make_shared<Node>(Node(100, 50));
    graph.addNode(c);
    graph.addNode(d);
    graph.addNode(e);
    graph.addNode(a);
    graph.addNode(b);
    graph.addNode(100, 100);
    graph.addNode(100, 100);
    graph.addNode(100, 100);
    graph.addNode(100, 100);
    graph.addNode(100, 100);
    graph.addNode(100, 100);
    graph.addNode(100, 100);
    graph.addNode(100, 100);
    graph.addNode(100, 100);
    graph.addEdge(a, b);
    graph.addEdge(a, c);
    graph.addEdge(b, c);
    graph.addEdge(a, d);
    graph.addEdge(a, e);
    graph.addEdge(b, d);
    graph.addEdge(b, e);
    graph.addEdge(c, d);
    graph.addEdge(c, e);
    graph.addEdge(d, e);
    graph.layout();
}

MainWindow::~MainWindow() {
    // Clean up and exit
    SDL_FreeSurface(fontSurface);
    SDL_DestroyTexture(fontTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

bool MainWindow::createWindow() {
    // Create a window
    window = SDL_CreateWindow("Graph Editor", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

    if (!window) {
	std::cout << "Failed to create window: " << SDL_GetError() << std::endl;
        return false;
    }

    // Create a renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (!renderer) {
	std::cout << "Failed to create renderer: " << SDL_GetError() << std::endl;
        return false;
    }
    fontSurface = SDL_LoadBMP("menu_font.bmp");
    if (!fontSurface) {
	    std::cout << "Failed to get font surface: " << SDL_GetError() << std::endl;
	    return false;
    }
    fontTexture = SDL_CreateTextureFromSurface(renderer, fontSurface);
    if (!fontTexture) {
	    std::cout << "Failed to get font texture: " << SDL_GetError() << std::endl;
	    return false;
    }

    return true;
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

    int charWidth = fontSurface->w / 26;
    int charHeight = fontSurface->h / 16;
    
    // Create the menu items
    std::string menuItems[3] = {"File", "Edit", "Help"};
    SDL_Rect menuRects[3];
    int menuWidth = 0;
    for (int i = 0; i < 3; i++) {
        // Create a texture for the menu item
        SDL_Rect charRect = {(i+1)*charWidth, 4*charHeight, charWidth, charHeight};
        SDL_Rect itemRect = {menuWidth, 0, charWidth, charHeight};
        SDL_RenderCopy(renderer, fontTexture, &charRect, &itemRect);

        // Set the position and dimensions of the menu item
        int x = menuWidth;
        int y = 0;
        int w = charWidth;
        int h = charHeight;
        menuRects[i] = {x, y, w, h};

        // Update the menu width
        menuWidth += charWidth;
    }


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
                        startNode = node;
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
			    std::cout << "delete node";
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
                if (dragging) 
		{
                    // check if the mouse was released on a node
                    bool releasedOnNode = false;
                    for (auto node : graph.getNodes()) {
                        if (node->isClicked(event.button.x, event.button.y)) {
                            // handle node release
                            if (startNode != node) {
                                 graph.addEdge(startNode, node);
                            }
                            releasedOnNode = true;
                            break;
                        }
                    }
                    if (!releasedOnNode) {
                        // handle canvas release
                        // graph.addNode(event.button.x, event.button.y);
			startNode->setPosition(event.button.x, event.button.y);
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
                else 
		{
                    for (auto node : graph.getNodes()) {
                        if (node->isSelected()) {
                            node->setPosition(event.motion.xrel, event.motion.yrel);
                        }
                    }
                }
                break;
            case SDL_WINDOWEVENT:
                    switch (event.window.event) {
                        case SDL_WINDOWEVENT_RESIZED:
                            // update window dimensions and layout
                            //WINDOW_WIDTH = event.window.data1;
                            //WINDOW_HEIGHT = event.window.data2;
                            graph.layout();
                            break;
                    }
                    break;
            default:
                break;
        }
        menuBar.handleInput(event);
    }
}
