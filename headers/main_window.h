#ifndef MAIN_WINDOW_H_
#define MAIN_WINDOW_H_

#include "graph.h"
#include "input_window.h"
#include "layout.h"
#include "menu.h"
#include "text.h"
#include "window.h"


class MainWindow : public Window {
public:
  MainWindow(const MainWindow &) = delete;
  MainWindow &operator=(const MainWindow &) = delete;
  static MainWindow &getInstance();

  bool init(const char *name, int width = WINDOW_WIDTH,
            int height = WINDOW_HEIGHT, bool isResizable = true,
            bool isShown = true) override;
  void mainLoop() override;

  void layoutGraph();
  void layoutFix();
  void showPopUpWindow(const std::string &title = "", const std::string &content = "",
                      const std::string &input = "");

  const std::unique_ptr<Graph> graph;
  const std::unique_ptr<MenuBar> menuBar;
  const std::unique_ptr<BitmapFont> font;
  const std::unique_ptr<InputWindow> inputWindow;

private:
  MainWindow();
  ~MainWindow();

  std::unique_ptr<Layout> m_layout;

  void renderWindow() override;
};

#endif
