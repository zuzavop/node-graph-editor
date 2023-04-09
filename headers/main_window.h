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
            int height = WINDOW_HEIGHT, bool isResizable = true,
            bool isShown = true) override;
  void mainLoop() override;

  std::shared_ptr<MainWindow> getPtr() { return shared_from_this(); }
  std::shared_ptr<Graph> getGraph() const { return m_graph; }
  std::shared_ptr<MenuBar> getMenu() const { return m_menuBar; }
  const std::string &getInputFromPopUp() { return m_input->getInput(); }
  bool popUpIsActive() { return m_input->isActive(); }

  void layoutGraph();
  void layoutFix();
  void saveToFile(std::ofstream &file);
  void loadFromFile(std::ifstream &file);
  void loadFromPSFile(std::ifstream &file);
  void exportToPSFile(std::ofstream &file);
  void setPopUpWindow(const std::string &title, const std::string &content,
                      const std::string &input = "");
  void setPopUpWarning(const std::string &warning);
  void showPopUpWindow();
  void setCallerPopUp(std::shared_ptr<PopUpCommand> caller);

private:
  std::shared_ptr<Graph> m_graph;
  Layout m_layout;
  std::shared_ptr<MenuBar> m_menuBar;
  std::shared_ptr<BitmapFont> m_font;
  std::shared_ptr<InputWindow> m_input;

  void renderWindow() override;
};

#endif
