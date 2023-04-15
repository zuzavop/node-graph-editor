#ifndef WINDOW_H
#define WINDOW_H

#ifndef _MSC_VER
#include <SDL2/SDL.h>
#else
#include "SDL.h"
#endif

#include <iostream>
#include <memory>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int WINDOW_PADDING = 15;

class Window {
public:
  virtual ~Window(){};
  virtual bool init(const char *name, int width = WINDOW_WIDTH,
                    int height = WINDOW_HEIGHT, bool isResizable = true,
                    bool isShown = true);
  virtual void mainLoop() = 0;
  void focus();

  int getWidth() const { return m_width; }
  int getHeight() const { return m_height; }
  SDL_Renderer *getRenderer() const { return m_renderer; }
  SDL_Window *getWindow() const { return m_window; }
  bool isFullScreen() const { return m_fullScreen; }

  void setDimension(int width, int height) {
    m_width = width;
    m_height = height;
  }
  void setFullScreen(bool fullScreen) { m_fullScreen = fullScreen; }
  void setRunning(bool isRunning) { m_running = isRunning; }

protected:
  Window(int width = 0, int height = 0);
  // window data
  SDL_Window *m_window;
  SDL_Renderer *m_renderer;

  int m_width;
  int m_height;

  bool m_fullScreen;
  bool m_running;
  bool m_shown;
  unsigned int m_id;

  virtual void renderWindow() = 0;
};

#endif
