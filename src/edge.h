#ifndef EDGE_H
#define EDGE_H

#include "node.h"

// Define a structure for a graph edge
class Edge {
    public:
        Edge(std::shared_ptr<Node> start, std::shared_ptr<Node> end, int n_weight) :
            startNode(start), endNode(end), weight(n_weight) {}

        std::shared_ptr<Node> getStart() const { return startNode; }
        std::shared_ptr<Node> getEnd() const { return endNode; }
        int getWeight() const { return weight; }

        void draw(SDL_Renderer* renderer); // draw the edge
    private:
        std::shared_ptr<Node> startNode; // starting node of the edge
        std::shared_ptr<Node> endNode; // ending node of the edge
        int weight; 
};

#endif