#include "main_window.h"
#include "events.h"

MainWindow &MainWindow::getInstance()
{
    static MainWindow singleInstance;
    return singleInstance;
}

MainWindow::MainWindow() : Window(), graph(std::make_unique<Graph>()), font(std::make_unique<BitmapFont>()),
      menuBar(std::make_unique<MenuBar>()), inputWindow(std::make_unique<InputWindow>()) {
  m_layout = std::make_unique<Layout>();
}

MainWindow::~MainWindow() {
  if (m_window) SDL_DestroyWindow(m_window);
  if (m_renderer) SDL_DestroyRenderer(m_renderer);
  SDL_Quit();
}

bool MainWindow::init(const char *name, int width, int height, bool isResizable,
                      bool isShown) {
  if (!Window::init(name)) {
    return false;
  }

  if (!font->buildFont("../assets/font.bmp", m_window, m_renderer)) {
    return false;
  }

  menuBar->init();

  return inputWindow->init();
}

void MainWindow::mainLoop() {
  MouseObserver mouseObserver;
  KeyboardObserver keyboardObserver;
  WindowObserver windowObserver;

  Subject events;
  events.attach(&mouseObserver);
  events.attach(&keyboardObserver);
  events.attach(&windowObserver);

  while (m_running) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        m_running = false;
      }
      if (event.window.windowID == m_id) {
        events.notify(event);
        menuBar->handleEvent(event);
      }

      inputWindow->handleEvent(event);
    }

    renderWindow();
    inputWindow->renderWindow();
  }
}

void MainWindow::renderWindow() {
  // clear the screen
  SDL_SetRenderDrawColor(m_renderer, WHITE.r, WHITE.g, WHITE.b, WHITE.a);
  SDL_RenderClear(m_renderer);

  graph->draw(m_renderer);
  menuBar->draw(m_renderer);

  SDL_RenderPresent(m_renderer);
}

void MainWindow::layoutGraph() {
  int startY = menuBar->getHeight() + WINDOW_PADDING;
  int startX = WINDOW_PADDING;
  m_layout->layout(graph, m_width - 2 * startX, m_height - startY - startX,
                  startX, startY);
}

void MainWindow::layoutFix() {
  int startY = menuBar->getHeight() + WINDOW_PADDING;
  int startX = WINDOW_PADDING;
  m_layout->layoutFix(graph, m_width - 2 * startX, m_height - startY - startX,
                     startX, startY);
}

void MainWindow::showPopUpWindow(const std::string &title,
                                const std::string &content,
                                const std::string &input) {
  inputWindow->setWarning();
  inputWindow->resetInput(input);
  inputWindow->setTitle(title);
  inputWindow->setDescription(content);
  inputWindow->focus();
  SDL_StartTextInput();
}
