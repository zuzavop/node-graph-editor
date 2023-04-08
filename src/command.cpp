#include "command.h"
#include "input_window.h"
#include "main_window.h"

namespace fs = std::filesystem;

bool SaveCommand::execute() {
  if (!active) {
    _window->setPopUpWindow("Save", "Enter the file path:");
    _window->setCallerPopUp(getptr());
    _window->showPopUpWindow();
    active = true;
  } else {
    if (!_window->popUpIsActive()) {
      const std::string address = _window->getInputFromPopUp();
      std::ofstream file(address);
      if (file.is_open()) {
        _window->saveToFile(file);
        file.close();
      } else {
        _window->setPopUpWarning("Failed to open file: " + address + "\n");
        return false;
      }
      active = false;
    }
  }
  return true;
}

bool SaveCommand::control(const std::string &input) {
  fs::path pathObj(input);

  if (pathObj.extension() == ".txt") {
    return true;
  } else {
    _window->setPopUpWarning("Please enter file with\nthe extension `.txt`.");
  }
  return false;
}

bool LoadCommand::execute() {
  if (!active) {
    _window->setPopUpWindow("Load", "Enter the file path:");
    _window->setCallerPopUp(getptr());
    _window->showPopUpWindow();
    active = true;
  } else {
    if (!_window->popUpIsActive()) {
      const std::string address = _window->getInputFromPopUp();

      fs::path pathObj(address);
      // open the file for reading
      std::ifstream file(address);

      if (file.is_open()) {
        if (pathObj.extension() == ".ps") {
          _window->loadFromPSFile(file);
        } else if (pathObj.extension() == ".txt") {
          _window->loadFromFile(file);
        }
        file.close();

        if (_window->getGraph()->needLayout()) {
          _window->layoutGraph();
          _window->getGraph()->wasLayout();
        }
      } else {
        _window->setPopUpWarning("Failed to open file: " + address + "\n");
        return false;
      }
      active = false;
    }
  }
  return true;
}

bool LoadCommand::control(const std::string &input) {
  fs::path pathObj(input);

  if (fs::exists(pathObj)) {
    if (pathObj.extension() == ".ps" || pathObj.extension() == ".txt") {
      return true;
    } else {
      _window->setPopUpWarning(
          "Please enter file with\nthe extension `.txt` or `.ps`.");
    }
  } else {
    _window->setPopUpWarning("Please enter existing file.");
  }
  return false;
}

bool ExportCommand::execute() {
  if (!active) {
    _window->setPopUpWindow("Export", "Enter the file path:");
    _window->setCallerPopUp(getptr());
    _window->showPopUpWindow();
    active = true;
  } else {
    if (!_window->popUpIsActive()) {
      const std::string address = _window->getInputFromPopUp();
      // open the file for writing
      std::ofstream file(address);
      if (file.is_open()) {
        _window->exportToPSFile(file);
        file.close();
      } else {
        _window->setPopUpWarning("Failed to open file: " + address + "\n");
        return false;
      }
      active = false;
    }
  }
  return true;
}

bool ExportCommand::control(const std::string &input) {
  fs::path pathObj(input);
  if (pathObj.extension() == ".ps") {
    return true;
  } else {
    _window->setPopUpWarning("Please enter file with\nthe extension `.ps`.");
  }
  return false;
}

bool NewNodeCommand::execute() {
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
  return true;
}

bool NewNodeCommand::control(const std::string &input) {
  if (input.size() < 4) {
    return true;
  } else {
    _window->setPopUpWarning("Please enter a name of up to 3 characters.");
  }
  return false;
}

bool LayoutCommand::execute() {
  _window->layoutGraph();
  return true;
}

bool NewCommand::execute() {
  _window->getGraph()->clearGraph();
  return true;
}

bool OkCommand::execute() {
  if (_window->getInput() != "") {
    if (_caller) {
      if (_caller->control(_window->getInput())) {
        _window->doneInput();
        if (_caller->execute())
          _window->hideWindow();
        else
          _window->doneInput(false);
      }
    }
  } else {
    _window->setWarning("Please enter value.");
  }
  return true;
}

void OkCommand::resetCallerState() {
  if (_caller)
    _caller->isActive(false);
}
