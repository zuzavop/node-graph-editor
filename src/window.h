#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>
#include <iostream>
#include <memory>

class Window {
    public:
	virtual ~Window() {};
	virtual bool init();
	virtual void mainLoop() = 0;

	// window dimensions
        int getWidth() { return mWidth; }
        int getHeight() { return mHeight; }
	SDL_Renderer* getRenderer() { return renderer; }
	SDL_Window* getWindow() { return window; }

	void setDimension(int w, int h) {
		mWidth = w;
		mHeight = h;
	}

	// window focii
        bool hasMouseFocus() { return mMouseFocus; }
        bool hasKeyboardFocus() { return mKeyboardFocus; }
	bool isFullScreen() { return mFullScreen; }
        bool isMinimized() { return mMinimized; }

	void setMouseFocus(bool mouseFocus) { mMouseFocus = mouseFocus; }
        void setKeyboardFocus(bool keyboardFocus) { mKeyboardFocus = keyboardFocus; }
	void setFullScreen(bool fullScreen) { mFullScreen = fullScreen; }
        void setMinimized(bool minimized) { mMinimized = minimized; }

    protected:
	Window(int w = 0, int h = 0);	
	// window data
	SDL_Window* window;
	SDL_Renderer* renderer;

	// window dimensions
	int mWidth;
	int mHeight;

	// window focus
        bool mMouseFocus;
        bool mKeyboardFocus;
        bool mFullScreen;
        bool mMinimized;

	bool running;

	virtual void renderWindow() = 0;
};

#endif
