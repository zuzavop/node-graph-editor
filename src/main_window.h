#ifndef WINDOW_H_
#define WINDOW_H_

#include "graph.h"
#include "menu.h"


class MainWindow {
    public:
        MainWindow();
        ~MainWindow();
        bool createWindow();
        void mainLoop();

	//Window dimensions
        int getWidth() { return mWidth; }
        int getHeight() { return mHeight; }

        //Window focii
        bool hasMouseFocus() { return mMouseFocus; }
        bool hasKeyboardFocus() { return mKeyboardFocus; }
        bool isMinimized() { return mMinimized; }

    private:
	// window data
        SDL_Window* window;

	// window dimensions
	int mWidth;
	int mHeight;

        SDL_Renderer* renderer;
        Graph graph;
        MenuBar menuBar;
        std::shared_ptr<Node> startNode;
        std::shared_ptr<Edge> selectedEdge;

	bool running;
        bool dragging;

	//Window focus
        bool mMouseFocus;
        bool mKeyboardFocus;
        bool mFullScreen;
        bool mMinimized;
	
	void renderWindow();
        void handleEvents();
};

#endif
