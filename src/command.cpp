#include "command.h"
#include "input_window.h"
#include "main_window.h"

namespace fs = std::filesystem;

void SaveCommand::execute() {
  if (!active) {
    _window->setPopUpWindow("Save", "Enter the file path:");
    _window->setCallerPopUp(getptr());
    _window->showPopUpWindow();
    active = true;
  } else {
    if (!_window->popUpIsActive()) {
      const std::string address = _window->getInputFromPopUp();
      _window->saveToFile(address);
      active = false;
    }
  }
}

bool SaveCommand::control(const std::string &input) {
  fs::path pathObj(input);

  if (pathObj.extension() == ".txt") {
    return true;
  }
  return false;
}

void LoadCommand::execute() {
  if (!active) {
    _window->setPopUpWindow("Load", "Enter the file path:");
    _window->setCallerPopUp(getptr());
    _window->showPopUpWindow();
    active = true;
  } else {
    if (!_window->popUpIsActive()) {
      const std::string address = _window->getInputFromPopUp();

      fs::path pathObj(address);

      if (pathObj.extension() == ".ps") {
        _window->loadFromPSFile(address);
      } else if (pathObj.extension() == ".txt") {
        _window->loadFromFile(address);
      }

      if (_window->getGraph()->needLayout()) {
        _window->layoutGraph();
        _window->getGraph()->wasLayout();
      }
      active = false;
    }
  }
}

bool LoadCommand::control(const std::string &input) {
  fs::path pathObj(input);

  if (fs::exists(pathObj)) {
    if (pathObj.extension() == ".ps" || pathObj.extension() == ".txt") {
      return true;
    }
  }
  return false;
}

void ExportCommand::execute() {
  if (!active) {
    _window->setPopUpWindow("Export", "Enter the file path:");
    _window->setCallerPopUp(getptr());
    _window->showPopUpWindow();
    active = true;
  } else {
    if (!_window->popUpIsActive()) {
      const std::string address = _window->getInputFromPopUp();
      _window->exportToPSFile(address);
      active = false;
    }
  }
}

bool ExportCommand::control(const std::string &input) {
  fs::path pathObj(input);
  if (pathObj.extension() == ".ps") {
    return true;
  }
  return false;
}

void NewNodeCommand::execute() {
  if (!active) {
    _window->setPopUpWindow("Node name", "Enter new name:", _node->getName());
    _window->setCallerPopUp(getptr());
    _window->showPopUpWindow();
    active = true;
  } else {
    if (!_window->popUpIsActive()) {
      const std::string name = _window->getInputFromPopUp();
      _node->setName(name);
      active = false;
    }
  }
}

bool NewNodeCommand::control(const std::string &input) {
	return true;
}

void LayoutCommand::execute() { _window->layoutGraph(); }

void NewCommand::execute() { _window->getGraph()->clearGraph(); }

void OkCommand::execute() {
  if (_window->getInput() != "") {
    if (_caller) {
      if (_caller->control(_window->getInput())) {
	_window->hideWindow();
      	_caller->execute();

      } else {
	      std::cout << "invalid input" << std::endl;
      }
    }
  } else {
	std::cout << "empty input" << std::endl;
  }
}

void OkCommand::resetCallerState() {
  if (_caller) _caller->isActive(false);
}
