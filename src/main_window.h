#ifndef MAIN_WINDOW_H_
#define MAIN_WINDOW_H_

#include "graph.h"
#include "menu.h"
#include "window.h"


class MainWindow : public Window, public std::enable_shared_from_this<MainWindow> {
    public:
	MainWindow();
        ~MainWindow();
        bool init() override;
        void mainLoop() override;

	std::shared_ptr<MainWindow> getptr() { return shared_from_this(); }
	std::shared_ptr<Graph> getGraph() { return std::make_shared<Graph>(graph); }	
    private:
        Graph graph;
        MenuBar menuBar;

        std::shared_ptr<Edge> selectedEdge;
	
	void renderWindow() override;
};

#endif
