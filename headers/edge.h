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

class Edge {
public:
  Edge(std::shared_ptr<Node> start, std::shared_ptr<Node> end,
       bool is_oriented = true)
      : startNode(start), endNode(end), selected(false), oriented(is_oriented) {
  }

  std::shared_ptr<Node> getSource() const { return startNode; }
  std::shared_ptr<Node> getTarget() const { return endNode; }
  bool isSelected() const { return selected; }
  bool isOriented() const { return oriented; }

  void setSelected(bool is_selected) { selected = is_selected; }
  void setOrientation(bool is_oriented) { oriented = is_oriented; }

  bool operator==(const Edge &other) const {
    return (startNode == other.getSource() && endNode == other.getTarget());
  }
  void switchNodes() {
    oriented = true;
    startNode.swap(endNode);
  }

  void draw(SDL_Renderer *renderer) const;

private:
  std::shared_ptr<Node> startNode; // starting node of the edge
  std::shared_ptr<Node> endNode;   // ending node of the edge
  bool selected;
  bool oriented;
};

#endif
