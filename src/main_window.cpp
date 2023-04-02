#include "main_window.h"

MainWindow::MainWindow() {
    running = true;
    dragging = false;
    mMouseFocus = false;
    mKeyboardFocus = false;
    mFullScreen = false;
    mMinimized = false;
    mWidth = 0;
    mHeight = 0;

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
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    window = NULL;
    renderer = NULL;
    SDL_Quit();
}

bool MainWindow::createWindow() {
    //Set texture filtering to linear
    if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
    {
	    std::cerr << "Warning: Linear texture filtering not enabled!" << std::endl;
    }

    // Create a window
    window = SDL_CreateWindow("Graph Editor", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    if (!window) {
	std::cout << "Failed to create window: " << SDL_GetError() << std::endl;
        return false;
    } else {
	mMouseFocus = true;
	mKeyboardFocus = true;
	mWidth = WINDOW_WIDTH;
	mHeight = WINDOW_HEIGHT;
    }

    // Create a renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (!renderer) {
	std::cout << "Failed to create renderer: " << SDL_GetError() << std::endl;
        return false;
    }

    return menuBar.init(renderer);
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
		else if (event.key.keysym.sym == SDLK_RETURN )
    		{
        	    if( mFullScreen )
        	    {
            		SDL_SetWindowFullscreen( window, SDL_FALSE );
            		mFullScreen = false;
        	    }
        	    else
        	    {
            		SDL_SetWindowFullscreen( window, SDL_TRUE );
            		mFullScreen = true;
            		mMinimized = false;
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
                        case SDL_WINDOWEVENT_SIZE_CHANGED:
            		    mWidth = event.window.data1;
            		    mHeight = event.window.data2;
       			    SDL_RenderPresent(renderer);
            		    break;

            		//Repaint on exposure
            		case SDL_WINDOWEVENT_EXPOSED:
            		    SDL_RenderPresent(renderer);
            		    break;

	 		//Mouse entered window
            		case SDL_WINDOWEVENT_ENTER:
            		    mMouseFocus = true;
            		    break;
            
            		//Mouse left window
            		case SDL_WINDOWEVENT_LEAVE:
            		    mMouseFocus = false;
            		    break;

            		//Window has keyboard focus
            		case SDL_WINDOWEVENT_FOCUS_GAINED:
            		    mKeyboardFocus = true;
            		    break;

            		//Window lost keyboard focus
            		case SDL_WINDOWEVENT_FOCUS_LOST:
            		    mKeyboardFocus = false;
            		    break;
	    		
			//Window minimized
            		case SDL_WINDOWEVENT_MINIMIZED:
            		    mMinimized = true;
		            break;

            		//Window maximized
            		case SDL_WINDOWEVENT_MAXIMIZED:
            		    mMinimized = false;
            		    break;
            
            		//Window restored
            		case SDL_WINDOWEVENT_RESTORED:
            		    mMinimized = false;
            		    break;		
		    }
		    break;
            default:
                break;
        }
        menuBar.handleEvent(event);
    }
}
