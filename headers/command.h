#ifndef COMMAND_H
#define COMMAND_H

#include <filesystem>
#include <memory>

#include "node.h"

class MainWindow;
class InputWindow;

class Command {
public:
  virtual bool execute() = 0;
};

class PopUpCommand : public Command,
                     public std::enable_shared_from_this<PopUpCommand> {
public:
  virtual bool execute() = 0;
  virtual bool control(const std::string &input) = 0;
  std::shared_ptr<PopUpCommand> getptr() { return shared_from_this(); }
  void isActive(bool is_active) { active = is_active; }

protected:
  PopUpCommand() : active(false) {}
  bool active;
};

class SaveCommand : public PopUpCommand {
public:
  SaveCommand(std::shared_ptr<MainWindow> window)
      : PopUpCommand(), _window(window) {}
  bool execute() override;
  bool control(const std::string &input) override;

private:
  std::shared_ptr<MainWindow> _window;
};

class LoadCommand : public PopUpCommand {
public:
  LoadCommand(std::shared_ptr<MainWindow> window)
      : PopUpCommand(), _window(window) {}
  bool execute() override;
  bool control(const std::string &input) override;

private:
  std::shared_ptr<MainWindow> _window;
};

class LayoutCommand : public Command {
public:
  LayoutCommand(std::shared_ptr<MainWindow> window) : _window(window) {}
  bool execute() override;

private:
  std::shared_ptr<MainWindow> _window;
};

class ExportCommand : public PopUpCommand {
public:
  ExportCommand(std::shared_ptr<MainWindow> window)
      : PopUpCommand(), _window(window) {}
  bool execute() override;
  bool control(const std::string &input) override;

private:
  std::shared_ptr<MainWindow> _window;
};

class NewCommand : public Command {
public:
  NewCommand(std::shared_ptr<MainWindow> window) : _window(window) {}
  bool execute() override;

private:
  std::shared_ptr<MainWindow> _window;
};

class NewNodeCommand : public PopUpCommand {
public:
  NewNodeCommand(std::shared_ptr<MainWindow> window, std::shared_ptr<Node> node)
      : PopUpCommand(), _window(window), _node(node) {}
  bool execute() override;
  bool control(const std::string &input) override;
  void resetNode(std::shared_ptr<Node> node) { _node = node; }

private:
  std::shared_ptr<MainWindow> _window;
  std::shared_ptr<Node> _node;
};

class OkCommand : public Command {
public:
  OkCommand(std::shared_ptr<InputWindow> window,
            std::shared_ptr<PopUpCommand> caller)
      : _window(window), _caller(caller) {}
  void setCaller(const std::shared_ptr<PopUpCommand> &caller) {
    _caller = caller;
  }
  std::shared_ptr<PopUpCommand> getCaller() { return _caller; }
  bool execute() override;
  void resetCallerState();

private:
  std::shared_ptr<InputWindow> _window;
  std::shared_ptr<PopUpCommand> _caller;
};

#endif
