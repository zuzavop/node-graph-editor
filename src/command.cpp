#include "command.h"
#include "main_window.h"

namespace fs = std::filesystem;

void SaveCommand::execute() { _window->saveToFile("../data/input4.txt"); }

void LoadCommand::execute() {
  /*std::string path = ".";
  std::cout << "Enter a file path: ";
  std::getline(std::cin, path);

  if (path.is_regular_file()) {
    std::string selectedFile = entry.path().string();
    std::cout << "Selected file: " << selectedFile << std::endl;
  }*/

  _window->loadFromPSFile("../data/output.ps");
  if (_window->getGraph()->needLayout()) {
    _window->layoutGraph();
    _window->getGraph()->wasLayout();
  }
}

void ExportCommand::execute() { _window->exportToPSFile("../data/output.ps"); }

void LayoutCommand::execute() { _window->layoutGraph(); }

void NewCommand::execute() { _window->getGraph()->clearGraph(); }
