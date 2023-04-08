#include "command.h"
#include "input_window.h"
#include "main_window.h"

namespace fs = std::filesystem;

bool SaveCommand::execute() {
  if (!m_active) {
    m_window->setPopUpWindow("Save", "Enter the file path:");
    m_window->setCallerPopUp(getPtr());
    m_window->showPopUpWindow();
    m_active = true;
  } else {
    if (!m_window->popUpIsActive()) {
      auto address = m_window->getInputFromPopUp();
      std::ofstream file(address);
      if (file.is_open()) {
        m_window->saveToFile(file);
        file.close();
      } else {
        m_window->setPopUpWarning("Failed to open file: " + address + "\n");
        return false;
      }
      m_active = false;
    }
  }
  return true;
}

bool SaveCommand::control(std::string_view input) {
  fs::path pathObj(input);

  if (pathObj.extension() != ".txt") {
    m_window->setPopUpWarning("Please enter file with\nthe extension `.txt`.");
    return false;
  }

  return true;
}

bool LoadCommand::execute() {
  if (!m_active) {
    m_window->setPopUpWindow("Load", "Enter the file path:");
    m_window->setCallerPopUp(getPtr());
    m_window->showPopUpWindow();
    m_active = true;
  } else {
    if (!m_window->popUpIsActive()) {
      auto address = m_window->getInputFromPopUp();
      fs::path pathObj(address);

      // open the file for reading
      std::ifstream file(address);
      if (file.is_open()) {
        if (pathObj.extension() == ".ps") {
          m_window->loadFromPSFile(file);
        } else if (pathObj.extension() == ".txt") {
          m_window->loadFromFile(file);
        }
        file.close();

        if (m_window->getGraph()->needLayout()) {
          m_window->layoutGraph();
          m_window->getGraph()->wasLayout();
        }
      } else {
        m_window->setPopUpWarning("Failed to open file: " + address + "\n");
        return false;
      }
      m_active = false;
    }
  }
  return true;
}

bool LoadCommand::control(std::string_view input) {
  fs::path pathObj(input);

  if (fs::exists(pathObj)) {
    if (pathObj.extension() != ".ps" && pathObj.extension() != ".txt") {
      m_window->setPopUpWarning(
          "Please enter file with\nthe extension `.txt` or `.ps`.");
      return false;
    }
  } else {
    m_window->setPopUpWarning("Please enter existing file.");
    return false;
  }

  return true;
}

bool ExportCommand::execute() {
  if (!m_active) {
    m_window->setPopUpWindow("Export", "Enter the file path:");
    m_window->setCallerPopUp(getPtr());
    m_window->showPopUpWindow();
    m_active = true;
  } else {
    if (!m_window->popUpIsActive()) {
      auto address = m_window->getInputFromPopUp();
      // open the file for writing
      std::ofstream file(address);
      if (file.is_open()) {
        m_window->exportToPSFile(file);
        file.close();
      } else {
        m_window->setPopUpWarning("Failed to open file: " + address + "\n");
        return false;
      }
      m_active = false;
    }
  }
  return true;
}

bool ExportCommand::control(std::string_view input) {
  fs::path pathObj(input);
  if (pathObj.extension() != ".ps") {
    m_window->setPopUpWarning("Please enter file with\nthe extension `.ps`.");
    return false;
  }
  return true;
}

bool NewNodeCommand::execute() {
  if (!m_active) {
    m_window->setPopUpWindow("Node name", "Enter new name:", _node->getName());
    m_window->setCallerPopUp(getPtr());
    m_window->showPopUpWindow();
    m_active = true;
  } else {
    if (!m_window->popUpIsActive()) {
      auto name = m_window->getInputFromPopUp();
      _node->setName(name);
      m_active = false;
    }
  }
  return true;
}

bool NewNodeCommand::control(std::string_view input) {
  if (input.size() > 4) {
    m_window->setPopUpWarning("Please enter a name of up to 4 characters.");
    return false;
  }
  return true;
}

bool LayoutCommand::execute() {
  m_window->layoutGraph();
  return true;
}

bool NewCommand::execute() {
  m_window->getGraph()->clearGraph();
  return true;
}

bool OkCommand::execute() {
  if (m_window->getInput() != "") {
    if (m_caller) {
      if (m_caller->control(m_window->getInput())) {
        m_window->doneInput();
        if (m_caller->execute()) {
          m_window->hideWindow();
        } else {
          m_window->doneInput(false);
        }
      }
    }
  } else {
    m_window->setWarning("Please enter value.");
  }
  return true;
}

void OkCommand::resetCallerState() {
  if (m_caller)
    m_caller->isActive(false);
}
