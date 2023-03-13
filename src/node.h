#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <vector>
#include <memory>
#include <random>
#include <cmath>
#include <fstream>
#include <sstream>
#include <cstring>

#include <SDL.h>

const int NODE_RADIUS = 20;

class Edge;

// Define a structure for a graph node
class Node {
public:
    Node(const std::string& n_name, float n_x, float n_y) : id(0), name(n_name), x(n_x), y(n_y), selected(false) {}
    Node(float n_x, float n_y) : id(0), x(n_x), y(n_y), name(""), selected(false) {}
    
    float getX() const { return x; }
    float getY() const { return y; }
    int getId() const { return id; }
    bool isSelected() const { return selected; }
    std::string getName() const { return name; }
    const std::vector<std::shared_ptr<Edge>>& getEdges() const {
        return edges;
    }

    void setX(float new_x) { x = new_x; }
    void setY(float new_y) { y = new_y; }
    void setName(std::string new_name) { name = new_name; }
    void setSelected(bool is_selected) { selected = is_selected; }

    void setPosition(float new_x, float new_y) { // set the position of the node
        x = new_x; 
        y = new_y;
    }

    bool contains(int x, int y, int radius) const {
        return std::pow(x - this->x, 2) + std::pow(y - this->y, 2) <= std::pow(radius, 2);
    }

    void addEdge(std::shared_ptr<Edge> edge);
    void removeEdge(const std::shared_ptr<Edge>& edge);
    
    void draw(SDL_Renderer* renderer, int radius) const; // draw the node
    bool isClicked(float mouseX, float mouseY); // check if the node is clicked

    bool operator==(const Node& other) const {
        return id == other.id;
    }
private:
    int id;
    std::string name;
    bool selected;
    float x, y; // position of the node
    std::vector<std::shared_ptr<Edge>> edges;
};

#endif