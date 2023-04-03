#include "main_window.h"
#include "events.h"

MainWindow::MainWindow() : Window() {
  _graph = std::make_shared<Graph>();

  std::shared_ptr<Node> a = std::make_shared<Node>(Node(150, 150));
  std::shared_ptr<Node> b = std::make_shared<Node>(Node(200, 150));
  std::shared_ptr<Node> c = std::make_shared<Node>(Node(50, 50));
  std::shared_ptr<Node> d = std::make_shared<Node>(Node(100, 100));
  std::shared_ptr<Node> e = std::make_shared<Node>(Node(100, 50));
  _graph->addNode(c);
  _graph->addNode(d);
  _graph->addNode(e);
  _graph->addNode(a);
  _graph->addNode(b);
  _graph->addNode(100, 100);
  _graph->addNode(100, 100);
  _graph->addNode(100, 100);
  _graph->addNode(100, 100);
  _graph->addNode(100, 100);
  _graph->addNode(100, 100);
  _graph->addNode(100, 100);
  _graph->addNode(100, 100);
  _graph->addNode(100, 100);
  _graph->addEdge(a, b);
  _graph->addEdge(a, c);
  _graph->addEdge(b, c);
  _graph->addEdge(a, d);
  _graph->addEdge(a, e);
  _graph->addEdge(b, d);
  _graph->addEdge(b, e);
  _graph->addEdge(c, d);
  _graph->addEdge(c, e);
  _graph->addEdge(d, e);
}

MainWindow::~MainWindow() {
  // Clean up and exit
  SDL_DestroyWindow(_window);
  SDL_DestroyRenderer(_renderer);
  SDL_Quit();
}

bool MainWindow::init(const char* name) {
  if (!Window::init(name)) {
    return false;
  }

  //_graph->saveToFile("file.txt");
  _graph->loadFromFile("../data/input.txt");

  layoutGraph();

  return _menuBar.init(_renderer);
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
  while (_running) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        _running = false;
      }
      events.notify(&event);
      _menuBar.handleEvent(event);
    }

    renderWindow();
  }
}

void MainWindow::renderWindow() {
  // clear the screen
  SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
  SDL_RenderClear(_renderer);

  // draw the _graph
  _graph->draw(_renderer);

  // draw the menu
  _menuBar.draw();

  // present the renderer
  SDL_RenderPresent(_renderer);
}

void MainWindow::layoutGraph() { _layout.layout(_graph, _width, _height); }

void MainWindow::saveToFile(const std::string &fileName) {
  _graph->saveToFile(fileName);
}

void MainWindow::loadFromFile(const std::string &fileName) {
  _graph->loadFromFile(fileName);
}
