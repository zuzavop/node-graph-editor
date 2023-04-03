#ifndef EDGE_H
#define EDGE_H

#include <cmath>
#include <fstream>
#include <iostream>
#include <memory>
#include <random>
#include <sstream>
#include <string>
#include <vector>

#include <SDL2/SDL.h>

class Node;

// Define a structure for a graph edge
class Edge {
public:
  Edge(std::shared_ptr<Node> start, std::shared_ptr<Node> end)
      : startNode(start), endNode(end), selected(false) {}

  std::shared_ptr<Node> getSource() const { return startNode; }

  std::shared_ptr<Node> getTarget() const { return endNode; }

  bool isSelected() const { return selected; }
  void setSelected(bool is_selected) { selected = is_selected; }

  bool operator==(const Edge &other) const {
    return (startNode == other.startNode && endNode == other.endNode) ||
           (startNode == other.endNode && endNode == other.startNode);
  }

  void draw(SDL_Renderer *renderer) const; // draw the edge
private:
  std::shared_ptr<Node> startNode; // starting node of the edge
  std::shared_ptr<Node> endNode;   // ending node of the edge
  bool selected;
};

#endif
