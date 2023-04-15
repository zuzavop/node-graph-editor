#include "events.h"
#include "main_window.h"

void Subject::attach(Observer *observer) { observers.push_back(observer); }

void Subject::detach(Observer *observer) {
  for (auto it = observers.begin(); it != observers.end(); ++it) {
    if (*it == observer) {
      observers.erase(it);
      break;
    }
  }
}

void Subject::notify(SDL_Event &event) {
  for (auto observer : observers) {
    observer->update(event);
  }
}

void MouseObserver::update(SDL_Event &event) {
  if (event.type == SDL_MOUSEBUTTONDOWN) {
    processButtonDown(event);
  } else if (event.type == SDL_MOUSEBUTTONUP) {
    processButtonUp(event);
  }
}

std::shared_ptr<Node> MouseObserver::findClickedNode(int x, int y) const {
    for (const auto& node : MainWindow::getInstance().graph->getNodes()) {
        if (node->isClicked(x, y)) {
            return node;
        }
    }
    return nullptr;
}

void MouseObserver::clearSelectedEdges() {
  for (const auto& edge : MainWindow::getInstance().graph->getEdges()) {
    edge->setSelected(false);
  }
}

void MouseObserver::clearSelectedNodes() {
  for (const auto &node : MainWindow::getInstance().graph->getNodes()) {
    node->setSelected(false);
  }
}

void MouseObserver::processButtonDown(SDL_Event &event) {
  if (MainWindow::getInstance().menuBar->clickedInMenu(event.button.x, event.button.y)) {
    return;
  }

  clearSelectedEdges();

  // check if the mouse was clicked on a node
  auto clickedNode = findClickedNode(event.button.x, event.button.y);
  if (clickedNode) {
      clickedNode->setSelected(true);
      m_dragging = true;
      m_startNode = clickedNode;
  } else {
      MainWindow::getInstance().graph->addNode(event.button.x, event.button.y);
  }
}

void MouseObserver::processButtonUp(SDL_Event &event) {
  if (MainWindow::getInstance().menuBar->clickedInMenu(event.button.x, event.button.y)) {
    return;
  }

  clearSelectedNodes();
  
  if (m_dragging) {
    auto clickedNode = findClickedNode(event.button.x, event.button.y);
    if (clickedNode) {
        if (m_startNode != clickedNode) {
        MainWindow::getInstance().graph->addEdge(m_startNode, clickedNode);
      } else {
        m_newCommand->resetNode(clickedNode);
        m_newCommand->execute();
      }
    } else {
        m_startNode->setPosition(event.button.x, event.button.y);
    }
    m_dragging = false;
  }
}

void KeyboardObserver::update(SDL_Event &event) {
  if (event.type == SDL_KEYDOWN) {
    // handle edge deletion
    if (event.key.keysym.sym == SDLK_DELETE ||
        event.key.keysym.sym == SDLK_BACKSPACE) {
      processDelete();
    } else if (event.key.keysym.sym == SDLK_F11) {
      processF11();
    } else if (event.key.keysym.sym == SDLK_ESCAPE) {
      processEscape();
    }
  }
}

void KeyboardObserver::processDelete() {
  // delete selected nodes and edges
  std::shared_ptr<Node> deletedNode;
  for (const auto &node : MainWindow::getInstance().graph->getNodes()) {
    if (node->isSelected()) {
      deletedNode = node;
      break;
    }
  }
  if (deletedNode) {
    MainWindow::getInstance().graph->removeNode(deletedNode);
  }

  std::shared_ptr<Edge> deletedEdge;
  for (const auto &edge : MainWindow::getInstance().graph->getEdges()) {
    if (edge->isSelected()) {
      deletedEdge = edge;
      break;
    }
  }
  if (deletedEdge) {
    MainWindow::getInstance().graph->removeEdge(deletedEdge);
  }
}

void KeyboardObserver::processF11() {
  if (!MainWindow::getInstance().isFullScreen()) {
    SDL_SetWindowFullscreen(MainWindow::getInstance().getWindow(), SDL_TRUE);
    MainWindow::getInstance().setFullScreen(true);
  }
}

void KeyboardObserver::processEscape() {
  if (MainWindow::getInstance().isFullScreen()) {
    SDL_SetWindowFullscreen(MainWindow::getInstance().getWindow(), SDL_FALSE);
    MainWindow::getInstance().setFullScreen(false);
  }
}

void WindowObserver::update(SDL_Event &event) {
  if (event.type == SDL_WINDOWEVENT) {
    switch (event.window.event) {
    case SDL_WINDOWEVENT_SIZE_CHANGED:
      MainWindow::getInstance().setDimension(event.window.data1, event.window.data2);
      MainWindow::getInstance().layoutFix();
      SDL_RenderPresent(MainWindow::getInstance().getRenderer());
      break;

    case SDL_WINDOWEVENT_EXPOSED:
      SDL_RenderPresent(MainWindow::getInstance().getRenderer());
      break;
    case SDL_WINDOWEVENT_CLOSE:
      MainWindow::getInstance().setRunning(false);
      break;
    }
  }
}
