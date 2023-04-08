#ifndef EVENTS_H
#define EVENTS_H

#include "command.h"
#include "node.h"

class MainWindow;

class Observer {
public:
  virtual ~Observer(){};
  virtual void update(SDL_Event &event) = 0;
};

class Subject {
public:
  void attach(Observer *observer);
  void detach(Observer *observer);
  void notify(SDL_Event &event);

private:
  std::vector<Observer *> observers;
};

class MouseObserver : public Observer {
public:
  MouseObserver(std::shared_ptr<MainWindow> window) : m_window(window), m_dragging(false) {
    m_newCommand = std::make_shared<NewNodeCommand>(window, m_startNode);
  }
  virtual ~MouseObserver() {}
  void update(SDL_Event &event) override;

private:
  void processButtonDown(SDL_Event &event);
  void processButtonUp(SDL_Event &event);

  std::shared_ptr<MainWindow> m_window;
  bool m_dragging;
  std::shared_ptr<Node> m_startNode;
  std::shared_ptr<NewNodeCommand> m_newCommand;
};

class KeyboardObserver : public Observer {
public:
  KeyboardObserver(std::shared_ptr<MainWindow> window) : m_window(window) {}
  virtual ~KeyboardObserver() {}
  void update(SDL_Event &event) override;

private:
  void processDelete();
  void processF11();
  void processEscape();

  std::shared_ptr<MainWindow> m_window;
};

class WindowObserver : public Observer {
public:
  WindowObserver(std::shared_ptr<MainWindow> window) : m_window(window) {}
  virtual ~WindowObserver() {}
  void update(SDL_Event &event) override;

private:
  std::shared_ptr<MainWindow> m_window;
};

#endif
