#ifndef MAIN_WINDOW_H_
#define MAIN_WINDOW_H_

#include "graph.h"
#include "layout.h"
#include "menu.h"
#include "window.h"


class MainWindow : public Window, public std::enable_shared_from_this<MainWindow> {
    public:
	MainWindow();
        ~MainWindow();
        bool init() override;
        void mainLoop() override;

	std::shared_ptr<MainWindow> getptr() { return shared_from_this(); }
	std::shared_ptr<Graph> getGraph() { return _graph; }	
    private:
	std::shared_ptr<Graph> _graph;
	Layout _layout;
	MenuBar _menuBar;
	
	void renderWindow() override;
};

#endif
