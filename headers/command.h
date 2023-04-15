#ifndef COMMAND_H
#define COMMAND_H

#include <filesystem>

#include "node.h"

class Command {
public:
  virtual ~Command(){};
  virtual void execute() = 0;
};

class PopUpCommand : public Command {
public:
  virtual ~PopUpCommand() {}
  virtual void execute() = 0;
  virtual bool realize() = 0;
  virtual bool control(std::string_view input) = 0;
};

class SaveCommand : public PopUpCommand {
public:
  SaveCommand() : PopUpCommand() { }
  virtual ~SaveCommand() {}
  void execute() override;
  bool realize() override;
  bool control(std::string_view input) override;
};

class LoadCommand : public PopUpCommand {
public:
  LoadCommand() : PopUpCommand() {}
  virtual ~LoadCommand() {}
  void execute() override;
  bool realize() override;
  bool control(std::string_view input) override;
};

class LayoutCommand : public Command {
public:
  LayoutCommand() {}
  virtual ~LayoutCommand() {}
  void execute() override;

};

class ExportCommand : public PopUpCommand {
public:
  ExportCommand() : PopUpCommand() {}
  virtual ~ExportCommand() {}
  void execute() override;
  bool realize() override;
  bool control(std::string_view input) override;
};

class NewCommand : public Command {
public:
  NewCommand() {}
  virtual ~NewCommand() {}
  void execute() override;
};

class NewNodeCommand : public PopUpCommand {
public:
  NewNodeCommand(std::shared_ptr<Node> node)
      : PopUpCommand(), m_node(node) {}
  virtual ~NewNodeCommand() {}
  void execute() override;
  bool realize() override;
  bool control(std::string_view input) override;
  void resetNode(std::shared_ptr<Node> node) { m_node = node; }

private:
  std::shared_ptr<Node> m_node;
};

class OkCommand : public Command {
public:
  OkCommand(PopUpCommand *caller) : m_caller(caller) {}
  virtual ~OkCommand() {}
  void setCaller(PopUpCommand *caller) { m_caller = caller; }
  void execute() override;

private:
  PopUpCommand *m_caller;
};

#endif
