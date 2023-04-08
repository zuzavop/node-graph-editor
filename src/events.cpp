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

void Subject::notify(SDL_Event *event) {
  for (auto observer : observers) {
    observer->update(event);
  }
}

void MouseObserver::update(SDL_Event *event) {
  if (event->type == SDL_MOUSEBUTTONDOWN) {
    processButtonDown(event);
  } else if (event->type == SDL_MOUSEBUTTONUP) {
    processButtonUp(event);
  }
}

void MouseObserver::processButtonDown(SDL_Event *event) {
  if (!window->getMenu()->clickedInMenu(event->button.x, event->button.y)) {
    for (const auto &edge : window->getGraph()->getEdges()) {
      edge->setSelected(false);
    }
    // check if the mouse was clicked on a node
    for (const auto &node : window->getGraph()->getNodes()) {
      if (node->isClicked(event->button.x, event->button.y)) {
        // handle node click
        node->setSelected(true);
        dragging = true;
        startNode = node;
      }
    }
    if (!dragging) {
      window->getGraph()->addNode(event->button.x, event->button.y);
    }
  }
}

void MouseObserver::processButtonUp(SDL_Event *event) {
  if (!window->getMenu()->clickedInMenu(event->button.x, event->button.y)) {
    // clear node selection
    for (const auto &node : window->getGraph()->getNodes()) {
      node->setSelected(false);
    }
    if (dragging) {
      // check if the mouse was released on a node
      bool releasedOnNode = false;
      for (const auto &node : window->getGraph()->getNodes()) {
        if (node->isClicked(event->button.x, event->button.y)) {
          if (startNode != node) {
            window->getGraph()->addEdge(startNode, node);
          } else {
            newCommand->resetNode(node);
            newCommand->execute();
          }
          releasedOnNode = true;
          break;
        }
      }
      if (!releasedOnNode) {
        startNode->setPosition(event->button.x, event->button.y);
      }
      dragging = false;
    }
  }
}

void KeyboardObserver::update(SDL_Event *event) {
  if (event->type == SDL_KEYDOWN) {
    // handle edge deletion
    if (event->key.keysym.sym == SDLK_DELETE ||
        event->key.keysym.sym == SDLK_BACKSPACE) {
      processDelete(event);
    } else if (event->key.keysym.sym == SDLK_F11) {
      processF11(event);
    } else if (event->key.keysym.sym == SDLK_ESCAPE) {
      processEscape(event);
    }
  }
}

void KeyboardObserver::processDelete(SDL_Event *event) {
  // delete selected nodes and edges
  std::shared_ptr<Node> deletedNode;
  for (const auto &node : window->getGraph()->getNodes()) {
    if (node->isSelected()) {
      deletedNode = node;
    }
  }
  if (deletedNode) {
    window->getGraph()->removeNode(deletedNode);
  }

  std::shared_ptr<Edge> deletedEdge;
  for (const auto &edge : window->getGraph()->getEdges()) {
    if (edge->isSelected()) {
      deletedEdge = edge;
    }
  }
  if (deletedEdge) {
    window->getGraph()->removeEdge(deletedEdge);
  }
}

void KeyboardObserver::processF11(SDL_Event *event) {
  if (!window->isFullScreen()) {
    SDL_SetWindowFullscreen(window->getWindow(), SDL_TRUE);
    window->setFullScreen(true);
  }
}

void KeyboardObserver::processEscape(SDL_Event *event) {
  if (window->isFullScreen()) {
    SDL_SetWindowFullscreen(window->getWindow(), SDL_FALSE);
    window->setFullScreen(false);
  }
}

void WindowObserver::update(SDL_Event *event) {
  if (event->type == SDL_WINDOWEVENT) {
    switch (event->window.event) {
    case SDL_WINDOWEVENT_SIZE_CHANGED:
      window->setDimension(event->window.data1, event->window.data2);
      window->layoutFix();
      SDL_RenderPresent(window->getRenderer());
      break;

    case SDL_WINDOWEVENT_EXPOSED:
      SDL_RenderPresent(window->getRenderer());
      break;
    case SDL_WINDOWEVENT_CLOSE:
      window->setRunning(false);
      break;
    }
  }
}
