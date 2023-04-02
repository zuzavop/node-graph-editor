#include "main_window.h"
#include "events.h"

MainWindow::MainWindow() : Window() {
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

bool MainWindow::init() {
    if (!Window::init()) {
	return false;
    }
    
    return menuBar.init(renderer);
}

void MainWindow::mainLoop() {
    MouseObserver mouseObserver(getptr());
    KeyboardObserver keyboardObserver(getptr()); 
    WindowObserver windowObserver(getptr());

    Subject events;
    events.attach(&mouseObserver);
    events.attach(&keyboardObserver);
    events.attach(&windowObserver);
    // Loop to handle events
    while (running) {
        SDL_Event event;
	while (SDL_PollEvent(&event)) {
	    if (event.type == SDL_QUIT) {
                running = false;
            }
	    events.notify(&event);
            menuBar.handleEvent(event);
	}

	renderWindow();
   }
}

void MainWindow::renderWindow() {
    // clear the screen
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    // draw the graph
    graph.draw(renderer);

    // draw the menu
    menuBar.draw();    

    // present the renderer
    SDL_RenderPresent(renderer);
}
