#ifndef HELPER_WINDOW_H
#define HELPER_WINDOW_H

#include "window.h"

class HelperWindow : public Window {
public:
  HelperWindow();
  ~HelperWindow();
  bool init(const char *name) override;
  void mainLoop() override;

private:
  void renderWindow() override;
};

#endif
