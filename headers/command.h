#ifndef COMMAND_H
#define COMMAND_H

#include <filesystem>

#include "node.h"

class MainWindow;
class InputWindow;

class Command {
public:
  virtual ~Command(){};
  virtual bool execute() = 0;
};

class PopUpCommand : public Command,
                     public std::enable_shared_from_this<PopUpCommand> {
public:
  virtual ~PopUpCommand() {}
  virtual bool execute() = 0;
  virtual bool control(std::string_view input) = 0;
  std::shared_ptr<PopUpCommand> getPtr() { return shared_from_this(); }
  void isActive(bool isActive) { m_active = isActive; }

protected:
  PopUpCommand() : m_active(false) {}
  bool m_active;
};

class SaveCommand : public PopUpCommand {
public:
  SaveCommand(std::shared_ptr<MainWindow> window)
      : PopUpCommand(), m_window(window) {}
  virtual ~SaveCommand() {}
  bool execute() override;
  bool control(std::string_view input) override;

private:
  std::shared_ptr<MainWindow> m_window;
};

class LoadCommand : public PopUpCommand {
public:
  LoadCommand(std::shared_ptr<MainWindow> window)
      : PopUpCommand(), m_window(window) {}
  virtual ~LoadCommand() {}
  bool execute() override;
  bool control(std::string_view input) override;

private:
  std::shared_ptr<MainWindow> m_window;
};

class LayoutCommand : public Command {
public:
  LayoutCommand(std::shared_ptr<MainWindow> window) : m_window(window) {}
  virtual ~LayoutCommand() {}
  bool execute() override;

private:
  std::shared_ptr<MainWindow> m_window;
};

class ExportCommand : public PopUpCommand {
public:
  ExportCommand(std::shared_ptr<MainWindow> window)
      : PopUpCommand(), m_window(window) {}
  virtual ~ExportCommand() {}
  bool execute() override;
  bool control(std::string_view input) override;

private:
  std::shared_ptr<MainWindow> m_window;
};

class NewCommand : public Command {
public:
  NewCommand(std::shared_ptr<MainWindow> window) : m_window(window) {}
  virtual ~NewCommand() {}
  bool execute() override;

private:
  std::shared_ptr<MainWindow> m_window;
};

class NewNodeCommand : public PopUpCommand {
public:
  NewNodeCommand(std::shared_ptr<MainWindow> window, std::shared_ptr<Node> node)
      : PopUpCommand(), m_window(window), _node(node) {}
  virtual ~NewNodeCommand() {}
  bool execute() override;
  bool control(std::string_view input) override;
  void resetNode(std::shared_ptr<Node> node) { _node = node; }

private:
  std::shared_ptr<MainWindow> m_window;
  std::shared_ptr<Node> _node;
};

class OkCommand : public Command {
public:
  OkCommand(std::shared_ptr<InputWindow> window,
            std::shared_ptr<PopUpCommand> caller)
      : m_window(window), m_caller(caller) {}
  virtual ~OkCommand() {}
  void setCaller(std::shared_ptr<PopUpCommand> caller) { m_caller = caller; }
  std::shared_ptr<PopUpCommand> getCaller() const { return m_caller; }
  bool execute() override;
  void resetCallerState();

private:
  std::shared_ptr<InputWindow> m_window;
  std::shared_ptr<PopUpCommand> m_caller;
};

#endif
