#ifndef NODE_H
#define NODE_H

#include "edge.h"

const int NODE_RADIUS = 20;

// Define a structure for a graph node
class Node {
public:
    Node(int n_x, int n_y) : x(n_x), y(n_y) {}
    virtual ~Node() {}

    int getX() const { return x; }
    int getY() const { return y; }

    void setX(int new_x) { x = new_x; }
    void setY(int new_y) { y = new_y; }

    void setPosition(int new_x, int new_y) { // set the position of the node
        x = new_x; 
        y = new_y;
    } 

    void addEdge(std::shared_ptr<Node> end, int weight);
    void removeEdge(std::shared_ptr<Node> end);

    const std::vector<std::shared_ptr<Edge>>& getEdges() const {
        return edges;
    }

    const std::vector<std::shared_ptr<Edge>>& getIncomingEdges() const {
        return incomingEdges;
    }

    void draw(SDL_Renderer* renderer); // draw the node
    bool isClicked(int mouseX, int mouseY); // check if the node is clicked

private:
    int x, y; // position of the node
    std::vector<std::shared_ptr<Edge>> edges;
    std::vector<std::shared_ptr<Edge>> incomingEdges;
};

#endif