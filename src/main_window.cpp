#include "main_window.h"
#include "events.h"

MainWindow::MainWindow() : Window() {
  m_graph = std::make_shared<Graph>();
  m_font = std::make_shared<BitmapFont>();
  m_menuBar = std::make_shared<MenuBar>(m_font);
  m_input = std::make_shared<InputWindow>();
}

MainWindow::~MainWindow() {
  SDL_DestroyWindow(m_window);
  SDL_DestroyRenderer(m_renderer);
  SDL_Quit();
}

bool MainWindow::init(const char *name, int width, int height) {
  if (!Window::init(name)) {
    return false;
  }

  if (!m_font->buildFont("../data/font.bmp", m_window, m_renderer)) {
    return false;
  }

  m_menuBar->init(getPtr());
  m_input->init();

  return true;
}

void MainWindow::mainLoop() {
  MouseObserver mouseObserver(getPtr());
  KeyboardObserver keyboardObserver(getPtr());
  WindowObserver windowObserver(getPtr());

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
        events.notify(&event);
        m_menuBar->handleEvent(&event);
      }

      m_input->handleEvent(&event);
    }

    renderWindow();
    m_input->renderWindow();
  }
}

void MainWindow::renderWindow() {
  // clear the screen
  SDL_SetRenderDrawColor(m_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  SDL_RenderClear(m_renderer);

  m_graph->draw(m_renderer, m_font);
  m_menuBar->draw(m_renderer);

  SDL_RenderPresent(m_renderer);
}

void MainWindow::layoutGraph() {
  int startY = m_menuBar->getHeight() + NODE_RADIUS * 2;
  int startX = NODE_RADIUS * 2;
  m_layout.layout(m_graph, m_width - 2 * startX, m_height - startY - startX,
                  startX, startY);
}

void MainWindow::layoutFix() {
  int startY = m_menuBar->getHeight() + NODE_RADIUS * 2;
  int startX = NODE_RADIUS * 2;
  m_layout.layoutFix(m_graph, m_width - 2 * startX, m_height - startY - startX,
                     startX, startY);
}

void MainWindow::saveToFile(std::ofstream &file) { m_graph->saveToFile(file); }

void MainWindow::loadFromFile(std::ifstream &file) {
  m_graph->loadFromFile(file);
}

void MainWindow::exportToPSFile(std::ofstream &file) {
  m_graph->exportToPSFile(file);
}

void MainWindow::loadFromPSFile(std::ifstream &file) {
  m_graph->loadFromPSFile(file);
}

void MainWindow::setPopUpWindow(const std::string &title,
                                const std::string &content,
                                const std::string &input) {
  m_input->setWarning();
  m_input->resetInput(input);
  m_input->setTitle(title);
  m_input->setDescription(content);
}

void MainWindow::setPopUpWarning(const std::string &warning) {
  m_input->setWarning(warning);
}

void MainWindow::showPopUpWindow() {
  m_input->focus();
  SDL_StartTextInput();
}

void MainWindow::setCallerPopUp(std::shared_ptr<PopUpCommand> caller) {
  m_input->setCaller(caller);
}
