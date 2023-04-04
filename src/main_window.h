#ifndef MAIN_WINDOW_H_
#define MAIN_WINDOW_H_

#include "graph.h"
#include "layout.h"
#include "menu.h"
#include "text.h"
#include "window.h"

class MainWindow : public Window,
                   public std::enable_shared_from_this<MainWindow> {
public:
  MainWindow();
  ~MainWindow();
  bool init(const char *name) override;
  void mainLoop() override;

  std::shared_ptr<MainWindow> getptr() { return shared_from_this(); }
  std::shared_ptr<Graph> getGraph() { return _graph; }
  std::shared_ptr<MenuBar> getMenu() { return _menuBar; }

  void layoutGraph();
  void layoutFix();
  void saveToFile(const std::string &fileName);
  void loadFromFile(const std::string &fileName);
  void exportToPSFile(const std::string &fileName);
  void loadFromPSFile(const std::string &fileName);

private:
  std::shared_ptr<Graph> _graph;
  Layout _layout;
  std::shared_ptr<MenuBar> _menuBar;
  std::shared_ptr<BitmapFont> _font;

  void renderWindow() override;
};

#endif
