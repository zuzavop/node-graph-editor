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
	// std::shared_ptr<SDL_Renderer> getRenderer() { return std::make_shared<SDL_Renderer>(renderer); }

	void setDimension(int w, int h) {
		mWidth = w;
		mHeight = h;
	}

	// window focii
        bool hasMouseFocus() { return mMouseFocus; }
        bool hasKeyboardFocus() { return mKeyboardFocus; }
	bool isFullScreen() { return mFullScreen; }
        bool isMinimized() { return mMinimized; }

	void setMouseFocus(bool m) { mMouseFocus = m; }
        void setKeyboardFocus(bool k) { mKeyboardFocus = k; }
	void setFullScreen(bool f) { mFullScreen = f; }
        void setMinimized(bool m) { mMinimized = m; }

    protected:
	Window(int w = 0, int h = 0) : window(NULL), renderer(NULL), mWidth(w), mHeight(h), running(true), mMouseFocus(false), mKeyboardFocus(false), mFullScreen(false), mMinimized(false) {}
	
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
