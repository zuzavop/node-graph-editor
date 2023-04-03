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
  virtual bool init(const char* name);
  virtual void mainLoop() = 0;

  // window dimensions
  int getWidth() { return _width; }
  int getHeight() { return _height; }
  SDL_Renderer *getRenderer() { return _renderer; }
  SDL_Window *getWindow() { return _window; }

  void setDimension(int width, int height) {
    _width = width;
    _height = height;
  }

  // window focii
  bool hasMouseFocus() { return _mouseFocus; }
  bool hasKeyboardFocus() { return _keyboardFocus; }
  bool isFullScreen() { return _fullScreen; }
  bool isMinimized() { return _minimized; }

  void setMouseFocus(bool mouseFocus) { _mouseFocus = mouseFocus; }
  void setKeyboardFocus(bool keyboardFocus) { _keyboardFocus = keyboardFocus; }
  void setFullScreen(bool fullScreen) { _fullScreen = fullScreen; }
  void setMinimized(bool minimized) { _minimized = minimized; }

protected:
  Window(int width = 0, int height = 0);
  // window data
  SDL_Window *_window;
  SDL_Renderer *_renderer;

  // window dimensions
  int _width;
  int _height;

  // window focus
  bool _mouseFocus;
  bool _keyboardFocus;
  bool _fullScreen;
  bool _minimized;

  bool _running;

  virtual void renderWindow() = 0;
};

#endif
