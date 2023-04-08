#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>
#include <iostream>
#include <memory>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

class Window {
public:
  virtual ~Window(){};
  virtual bool init(const char *name, int width = WINDOW_WIDTH,
                    int height = WINDOW_HEIGHT);
  virtual void mainLoop() = 0;
  void focus();

  int getWidth() { return _width; }
  int getHeight() { return _height; }
  SDL_Renderer *getRenderer() { return _renderer; }
  SDL_Window *getWindow() { return _window; }
  bool isFullScreen() { return _fullScreen; }

  void setDimension(int width, int height) {
    _width = width;
    _height = height;
  }
  void setFullScreen(bool fullScreen) { _fullScreen = fullScreen; }
  void setRunning(bool is_running) { _running = is_running; }

protected:
  Window(int width = 0, int height = 0);
  // window data
  SDL_Window *_window;
  SDL_Renderer *_renderer;

  int _width;
  int _height;

  bool _fullScreen;
  bool _running;
  bool _shown;
  int _id;

  virtual void renderWindow() = 0;
};

#endif
