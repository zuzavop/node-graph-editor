#ifndef LAYOUT_H
#define LAYOUT_H

#include <memory>
#include <vector>

class Graph;

class Layout {
    public:
	Layout() {}
	
	void layout(std::shared_ptr<Graph> graph, int width, int height);

    private:
	void fruchtermanReingold(std::shared_ptr<Graph> graph, int iterations, float k, int width, int height);
        void layoutBruteForce(std::shared_ptr<Graph> graph);
};

#endif
