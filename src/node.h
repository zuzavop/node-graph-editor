#ifndef NODE_H
#define NODE_H

#include "edge.h"

const int NODE_RADIUS = 20;

// Define a structure for a graph node
class Node {
public:
    Node(const std::string& n_name, float n_x, float n_y) : name(n_name), x(n_x), y(n_y) {}
    virtual ~Node() {}

    float getX() const { return x; }
    float getY() const { return y; }


    void setX(float new_x) { x = new_x; }
    void setY(float new_y) { y = new_y; }

    void setPosition(float new_x, float new_y) { // set the position of the node
        x = new_x; 
        y = new_y;
    } 

    void addEdge(std::shared_ptr<Edge> edge);
    void removeEdge(std::shared_ptr<Edge>& edge);

    const std::vector<std::shared_ptr<Edge>>& getEdges() const {
        return edges;
    }

    void draw(SDL_Renderer* renderer); // draw the node
    bool isClicked(float mouseX, float mouseY); // check if the node is clicked

private:
    std::string name;
    float x, y; // position of the node
    std::vector<std::shared_ptr<Edge>> edges;
};

#endif