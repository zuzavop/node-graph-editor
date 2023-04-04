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
	  if (!window->getMenu()->clickedInMenu(event->button.x, event->button.y)) {
    // check if the mouse was clicked on a node
    for (auto node : window->getGraph()->getNodes()) {
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
  } else if (event->type == SDL_MOUSEBUTTONUP) {
	  if (!window->getMenu()->clickedInMenu(event->button.x, event->button.y)) {
    // clear node selection
    for (auto node : window->getGraph()->getNodes()) {
      node->setSelected(false);
    }
    if (dragging) {
      // check if the mouse was released on a node
      bool releasedOnNode = false;
      for (auto node : window->getGraph()->getNodes()) {
        if (node->isClicked(event->button.x, event->button.y)) {
          if (startNode != node) {
            window->getGraph()->addEdge(startNode, node);
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
}

void KeyboardObserver::update(SDL_Event *event) {
  if (event->type == SDL_KEYDOWN) {
    // handle edge deletion
    if (event->key.keysym.sym == SDLK_DELETE) {
      std::cout << "delete" << std::endl;
      // delete selected nodes and edges
      for (auto node : window->getGraph()->getNodes()) {
        if (node->isSelected()) {
          std::cout << "delete node";
          window->getGraph()->removeNode(node);
        }
      }
      for (auto edge : window->getGraph()->getEdges()) {
        if (edge->isSelected()) {
          window->getGraph()->removeEdge(edge);
        }
      }
    } else if (event->key.keysym.sym == SDLK_RETURN) {
      if (window->isFullScreen()) {
        SDL_SetWindowFullscreen(window->getWindow(), SDL_FALSE);
        window->setFullScreen(false);
      } else {
        SDL_SetWindowFullscreen(window->getWindow(), SDL_TRUE);
        window->setFullScreen(true);
        window->setMinimized(false);
      }
    }
  }
}

void WindowObserver::update(SDL_Event *event) {
  if (event->type == SDL_WINDOWEVENT) {
    switch (event->window.event) {
    case SDL_WINDOWEVENT_SIZE_CHANGED:
      window->setDimension(event->window.data1, event->window.data2);
      SDL_RenderPresent(window->getRenderer());
      break;

    case SDL_WINDOWEVENT_EXPOSED:
      SDL_RenderPresent(window->getRenderer());
      break;

    case SDL_WINDOWEVENT_ENTER:
      window->setMouseFocus(true);
      break;

    case SDL_WINDOWEVENT_LEAVE:
      window->setMouseFocus(false);
      break;

    case SDL_WINDOWEVENT_FOCUS_GAINED:
      window->setKeyboardFocus(true);
      break;

    case SDL_WINDOWEVENT_FOCUS_LOST:
      window->setKeyboardFocus(false);
      break;

    case SDL_WINDOWEVENT_MINIMIZED:
      window->setMinimized(true);
      break;

    case SDL_WINDOWEVENT_MAXIMIZED:
      window->setMinimized(false);
      break;

    case SDL_WINDOWEVENT_RESTORED:
      window->setMinimized(false);
      break;
    }
  }
}
