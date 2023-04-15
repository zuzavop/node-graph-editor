#include "command.h"
#include "main_window.h"
#include "input_window.h"

namespace fs = std::filesystem;

void SaveCommand::execute() {
  if (MainWindow::getInstance().graph->getNodes().size() == 0) {
    return;
  }
  MainWindow::getInstance().showPopUpWindow("Save", "Enter the file path:");
  MainWindow::getInstance().inputWindow->setCaller(this);
}

bool SaveCommand::realize() {
  if (MainWindow::getInstance().inputWindow->isActive()) {
    return false;
  }
  auto address = MainWindow::getInstance().inputWindow->getInput();
  std::ofstream file(address);
  if (file.is_open()) {
    MainWindow::getInstance().graph->saveToFile(file);
    file.close();
  } else {
    MainWindow::getInstance().inputWindow->setWarning("Failed to open file: " + address + "\n");
    return false;
  }
  return true;
}

bool SaveCommand::control(std::string_view input) {
  fs::path pathObj(input);

  if (pathObj.extension() != ".txt") {
    MainWindow::getInstance().inputWindow->setWarning("Please enter file with\nthe extension `.txt`.");
    return false;
  }

  return true;
}

void LoadCommand::execute() {
  MainWindow::getInstance().showPopUpWindow("Load", "Enter the file path:");
  MainWindow::getInstance().inputWindow->setCaller(this);
}

bool LoadCommand::realize() {
  if (MainWindow::getInstance().inputWindow->isActive()) {
    return false;
  }

  auto address = MainWindow::getInstance().inputWindow->getInput();
  fs::path pathObj(address);

  // open the file for reading
  std::ifstream file(address);
  if (file.is_open()) {
    if (pathObj.extension() == ".ps") {
      MainWindow::getInstance().graph->loadFromPSFile(file);
    } else if (pathObj.extension() == ".txt") {
      MainWindow::getInstance().graph->loadFromFile(file);
    }
    file.close();

    if (MainWindow::getInstance().graph->needLayout()) {
      MainWindow::getInstance().layoutGraph();
      MainWindow::getInstance().graph->wasLayout();
    }
  } else {
    MainWindow::getInstance().inputWindow->setWarning("Failed to open file: " + address + "\n");
    return false;
  }
  return true;
}

bool LoadCommand::control(std::string_view input) {
  fs::path pathObj(input);

  if (fs::exists(pathObj)) {
    if (pathObj.extension() != ".ps" && pathObj.extension() != ".txt") {
      MainWindow::getInstance().inputWindow->setWarning(
          "Please enter file with\nthe extension `.txt` or `.ps`.");
      return false;
    }
  } else {
    MainWindow::getInstance().inputWindow->setWarning("Please enter existing file.");
    return false;
  }

  return true;
}

void ExportCommand::execute() {
  if (MainWindow::getInstance().graph->getNodes().size() == 0) {
    return;
  }
  MainWindow::getInstance().showPopUpWindow("Export", "Enter the file path:");
  MainWindow::getInstance().inputWindow->setCaller(this);
}

bool ExportCommand::realize() {
  if (MainWindow::getInstance().inputWindow->isActive()) {
    return false;
  }

  auto address = MainWindow::getInstance().inputWindow->getInput();
  // open the file for writing
  std::ofstream file(address);
  if (file.is_open()) {
    MainWindow::getInstance().graph->exportToPSFile(file);
    file.close();
  } else {
    MainWindow::getInstance().inputWindow->setWarning("Failed to open file: " + address + "\n");
    return false;
  }
  return true;
}

bool ExportCommand::control(std::string_view input) {
  fs::path pathObj(input);
  if (pathObj.extension() != ".ps") {
    MainWindow::getInstance().inputWindow->setWarning("Please enter file with\nthe extension `.ps`.");
    return false;
  }
  return true;
}

void NewNodeCommand::execute() {
  MainWindow::getInstance().showPopUpWindow("Node name", "Enter new name:", m_node->getName());
  MainWindow::getInstance().inputWindow->setCaller(this);
}

bool NewNodeCommand::realize() {
  if (!MainWindow::getInstance().inputWindow->isActive()) {
    auto name = MainWindow::getInstance().inputWindow->getInput();
    m_node->setName(name);
    return true;
  }
  return false;
}

bool NewNodeCommand::control(std::string_view input) {
  if (input.size() > 4) {
    MainWindow::getInstance().inputWindow->setWarning("Please enter a name of up to 4 characters.");
    return false;
  }
  return true;
}

void LayoutCommand::execute() {
  MainWindow::getInstance().layoutGraph();
}

void NewCommand::execute() {
  MainWindow::getInstance().graph->clearGraph();
}

void OkCommand::execute() {
  const auto input = MainWindow::getInstance().inputWindow->getInput();
  if (!input.empty()) {
    if (m_caller && m_caller->control(input)) {
      MainWindow::getInstance().inputWindow->doneInput();
      if (m_caller->realize()) {
        MainWindow::getInstance().inputWindow->hideWindow();
      } else {
        MainWindow::getInstance().inputWindow->doneInput(false);
      }
    }
  } else {
    MainWindow::getInstance().inputWindow->setWarning("Please enter value.");
  }
}
