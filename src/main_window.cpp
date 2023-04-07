#include "main_window.h"
#include "events.h"

MainWindow::MainWindow() : Window() {
  _graph = std::make_shared<Graph>();
  _font = std::make_shared<BitmapFont>();
  _menuBar = std::make_shared<MenuBar>(_font);
}

MainWindow::~MainWindow() {
  SDL_DestroyWindow(_window);
  SDL_DestroyRenderer(_renderer);
  SDL_Quit();
}

bool MainWindow::init(const char *name) {
  if (!Window::init(name)) {
    return false;
  }

  if (!_font->buildFont("../data/font.bmp", _window, _renderer)) {
    return false;
  }

  _menuBar->init(getptr());

  return true;
}

void MainWindow::mainLoop() {
  MouseObserver mouseObserver(getptr());
  KeyboardObserver keyboardObserver(getptr());
  WindowObserver windowObserver(getptr());

  Subject events;
  events.attach(&mouseObserver);
  events.attach(&keyboardObserver);
  events.attach(&windowObserver);

  while (_running) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        _running = false;
      }
      events.notify(&event);
      _menuBar->handleEvent(&event);
    }

    renderWindow();
  }
}

void MainWindow::renderWindow() {
  // clear the screen
  SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
  SDL_RenderClear(_renderer);

  _graph->draw(_renderer, _font);
  _menuBar->draw(_renderer);

  SDL_RenderPresent(_renderer);
}

void MainWindow::layoutGraph() {
  int startY = _menuBar->getHeight() + NODE_RADIUS * 2;
  int startX = NODE_RADIUS * 2;
  _layout.layout(_graph, _width - 2 * startX, _height - startY - startX, startX,
                 startY);
}

void MainWindow::layoutFix() {
  int startY = _menuBar->getHeight() + NODE_RADIUS * 2;
  int startX = NODE_RADIUS * 2;
  _layout.layoutFix(_graph, _width - 2 * startX, _height - startY - startX,
                    startX, startY);
}

void MainWindow::saveToFile(const std::string &fileName) {
  _graph->saveToFile(fileName);
}

void MainWindow::loadFromFile(const std::string &fileName) {
  _graph->loadFromFile(fileName);
}

void MainWindow::exportToPSFile(const std::string &fileName) {
  _graph->exportToPSFile(fileName);
}

void MainWindow::loadFromPSFile(const std::string &fileName) {
  _graph->loadFromPSFile(fileName);
}
