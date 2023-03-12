#ifndef EDGE_H
#define EDGE_H

#include "node.h"

// Define a structure for a graph edge
class Edge {
    public:
        Edge(std::shared_ptr<Node> start, std::shared_ptr<Node> end) :
            startNode(start), endNode(end) {}

        std::shared_ptr<Node> getStart() const { return startNode; }
        std::shared_ptr<Node> getEnd() const { return endNode; }

        bool operator==(const Edge& other) const {
            return (startNode == other.startNode && endNode == other.endNode) 
            || (startNode == other.endNode && endNode == other.startNode);
        }

        void draw(SDL_Renderer* renderer); // draw the edge
    private:
        std::shared_ptr<Node> startNode; // starting node of the edge
        std::shared_ptr<Node> endNode; // ending node of the edge
};

#endif