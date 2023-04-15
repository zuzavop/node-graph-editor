#ifndef EVENTS_H
#define EVENTS_H

#include "command.h"
#include "node.h"

class Observer {
public:
  virtual ~Observer() = default;
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
  MouseObserver() : m_dragging(false) {
    m_newCommand = std::make_unique<NewNodeCommand>(m_startNode);
  }
  virtual ~MouseObserver() = default;
  void update(SDL_Event &event) override;

private:
  void processButtonDown(SDL_Event &event);
  void processButtonUp(SDL_Event &event);

  std::shared_ptr<Node> findClickedNode(int x, int y) const;
  void clearSelectedEdges();
  void clearSelectedNodes();

  bool m_dragging;
  std::shared_ptr<Node> m_startNode;
  std::unique_ptr<NewNodeCommand> m_newCommand;
};

class KeyboardObserver : public Observer {
public:
  KeyboardObserver()  = default;
  virtual ~KeyboardObserver()  = default;
  void update(SDL_Event &event) override;

private:
  void processDelete();
  void processF11();
  void processEscape();
};

class WindowObserver : public Observer {
public:
  WindowObserver()  = default;
  virtual ~WindowObserver()  = default;
  void update(SDL_Event &event) override;
};

#endif
