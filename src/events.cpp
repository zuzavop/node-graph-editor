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

void MouseObserver::processButtonDown(SDL_Event &event) {
  if (!m_window->getMenu()->clickedInMenu(event.button.x, event.button.y)) {
    for (const auto &edge : m_window->getGraph()->getEdges()) {
      edge->setSelected(false);
    }
    // check if the mouse was clicked on a node
    for (const auto &node : m_window->getGraph()->getNodes()) {
      if (node->isClicked(event.button.x, event.button.y)) {
        // handle node click
        node->setSelected(true);
        m_dragging = true;
        m_startNode = node;
      }
    }
    if (!m_dragging) {
      m_window->getGraph()->addNode(event.button.x, event.button.y);
    }
  }
}

void MouseObserver::processButtonUp(SDL_Event &event) {
  if (!m_window->getMenu()->clickedInMenu(event.button.x, event.button.y)) {
    // clear node selection
    for (const auto &node : m_window->getGraph()->getNodes()) {
      node->setSelected(false);
    }
    if (m_dragging) {
      // check if the mouse was released on a node
      bool releasedOnNode = false;
      for (const auto &node : m_window->getGraph()->getNodes()) {
        if (node->isClicked(event.button.x, event.button.y)) {
          if (m_startNode != node) {
            m_window->getGraph()->addEdge(m_startNode, node);
          } else {
            m_newCommand->resetNode(node);
            m_newCommand->execute();
          }
          releasedOnNode = true;
          break;
        }
      }
      if (!releasedOnNode) {
        m_startNode->setPosition(event.button.x, event.button.y);
      }
      m_dragging = false;
    }
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
  for (const auto &node : m_window->getGraph()->getNodes()) {
    if (node->isSelected()) {
      deletedNode = node;
    }
  }
  if (deletedNode) {
    m_window->getGraph()->removeNode(deletedNode);
  }

  std::shared_ptr<Edge> deletedEdge;
  for (const auto &edge : m_window->getGraph()->getEdges()) {
    if (edge->isSelected()) {
      deletedEdge = edge;
    }
  }
  if (deletedEdge) {
    m_window->getGraph()->removeEdge(deletedEdge);
  }
}

void KeyboardObserver::processF11() {
  if (!m_window->isFullScreen()) {
    SDL_SetWindowFullscreen(m_window->getWindow(), SDL_TRUE);
    m_window->setFullScreen(true);
  }
}

void KeyboardObserver::processEscape() {
  if (m_window->isFullScreen()) {
    SDL_SetWindowFullscreen(m_window->getWindow(), SDL_FALSE);
    m_window->setFullScreen(false);
  }
}

void WindowObserver::update(SDL_Event &event) {
  if (event.type == SDL_WINDOWEVENT) {
    switch (event.m_window.event) {
    case SDL_WINDOWEVENT_SIZE_CHANGED:
      m_window->setDimension(event.m_window.data1, event.m_window.data2);
      m_window->layoutFix();
      SDL_RenderPresent(m_window->getRenderer());
      break;

    case SDL_WINDOWEVENT_EXPOSED:
      SDL_RenderPresent(m_window->getRenderer());
      break;
    case SDL_WINDOWEVENT_CLOSE:
      m_window->setRunning(false);
      break;
    }
  }
}
