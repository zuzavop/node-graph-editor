#ifndef MAIN_WINDOW_H_
#define MAIN_WINDOW_H_

#include "graph.h"
#include "input_window.h"
#include "layout.h"
#include "menu.h"
#include "text.h"
#include "window.h"

class MainWindow : public Window,
                   public std::enable_shared_from_this<MainWindow> {
public:
  MainWindow();
  ~MainWindow();
  bool init(const char *name, int width = WINDOW_WIDTH,
            int height = WINDOW_HEIGHT) override;
  void mainLoop() override;

  std::shared_ptr<MainWindow> getptr() { return shared_from_this(); }
  std::shared_ptr<Graph> getGraph() { return _graph; }
  std::shared_ptr<MenuBar> getMenu() { return _menuBar; }

  void layoutGraph();
  void layoutFix();
  void saveToFile(std::ofstream &file);
  void loadFromFile(std::ifstream &file);
  void loadFromPSFile(std::ifstream &file);
  void exportToPSFile(std::ofstream &file);
  void setPopUpWindow(const std::string &title, const std::string &content, const std::string &input = "");
  void setPopUpWarning(const std::string &warning);
  void showPopUpWindow();
  void setCallerPopUp(const std::shared_ptr<PopUpCommand> &caller);
  const std::string &getInputFromPopUp() { return _input->getInput(); }
  bool popUpIsActive() { return _input->isActive(); }

private:
  std::shared_ptr<Graph> _graph;
  Layout _layout;
  std::shared_ptr<MenuBar> _menuBar;
  std::shared_ptr<BitmapFont> _font;
  std::shared_ptr<InputWindow> _input;

  void renderWindow() override;
};

#endif
