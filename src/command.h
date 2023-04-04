#ifndef COMMAND_H
#define COMMAND_H

#include <memory>

class MainWindow;

class Command {
public:
  virtual void execute() = 0;
};

class QuitCommand : public Command {
public:
  QuitCommand(bool &running) : _running(running) {}
  void execute() override { _running = false; }

private:
  bool &_running;
};

class SaveCommand : public Command {
public:
  SaveCommand(std::shared_ptr<MainWindow> window) : _window(window) {}
  void execute() override;

private:
  std::shared_ptr<MainWindow> _window;
};

class LoadCommand : public Command {
public:
  LoadCommand(std::shared_ptr<MainWindow> window) : _window(window) {}
  void execute() override;

private:
  std::shared_ptr<MainWindow> _window;
};

class LoadFromPSCommand : public Command {
public:
  LoadFromPSCommand(std::shared_ptr<MainWindow> window) : _window(window) {}
  void execute() override;

private:
  std::shared_ptr<MainWindow> _window;
};

class LayoutCommand : public Command {
public:
  LayoutCommand(std::shared_ptr<MainWindow> window) : _window(window) {}
  void execute() override;

private:
  std::shared_ptr<MainWindow> _window;
};

class ExportCommand : public Command {
public:
  ExportCommand(std::shared_ptr<MainWindow> window) : _window(window) {}
  void execute() override;

private:
  std::shared_ptr<MainWindow> _window;
};

#endif
