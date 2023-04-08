#ifndef EVENTS_H
#define EVENTS_H

#include "node.h"
#include "command.h"

class MainWindow;

class Observer {
public:
  virtual void update(SDL_Event *event) = 0;
};

class Subject {
public:
  void attach(Observer *observer);

  void detach(Observer *observer);

  void notify(SDL_Event *event);

private:
  std::vector<Observer *> observers;
};

class MouseObserver : public Observer {
public:
  MouseObserver(std::shared_ptr<MainWindow> w) : window(w), dragging(false) {
    newCommand = std::make_shared<NewNodeCommand>(w, startNode);
  }
  void update(SDL_Event *event) override;

private:
  void processButtonDown(SDL_Event *event);
  void processButtonUp(SDL_Event *event);
  std::shared_ptr<MainWindow> window;
  bool dragging;
  std::shared_ptr<Node> startNode;
  std::shared_ptr<NewNodeCommand> newCommand;
};

class KeyboardObserver : public Observer {
public:
  KeyboardObserver(std::shared_ptr<MainWindow> w) : window(w) {}
  void update(SDL_Event *event) override;

private:
  void processDelete(SDL_Event *event);
  void processF11(SDL_Event *event);
  void processEscape(SDL_Event *event);
  std::shared_ptr<MainWindow> window;
};

class WindowObserver : public Observer {
public:
  WindowObserver(std::shared_ptr<MainWindow> w) : window(w) {}
  void update(SDL_Event *event) override;

private:
  std::shared_ptr<MainWindow> window;
};

#endif
