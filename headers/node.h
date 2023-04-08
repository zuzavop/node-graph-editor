#ifndef NODE_H
#define NODE_H

#include <algorithm>
#include <fstream>
#include <iostream>
#include <memory>
#include <random>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

#include <SDL2/SDL.h>

#include "text.h"

const int NODE_RADIUS = 10;

class Edge;

class Node {
public:
  Node(const std::string &n_name, float n_x, float n_y)
      : id(0), name(n_name), selected(false) {
    position.x = n_x;
    position.y = n_y;
  }

  Node(float n_x, float n_y) : id(0), name(""), selected(false) {
    position.x = n_x;
    position.y = n_y;
  }

  Node(const std::string &n_name, float n_x, float n_y, int n_id)
      : id(n_id), name(n_name), selected(false) {
    position.x = n_x;
    position.y = n_y;
  }

  float getX() const { return position.x; }
  float getY() const { return position.y; }
  int getId() const { return id; }
  bool isSelected() const { return selected; }
  std::string getName() const { return name; }
  const std::vector<std::shared_ptr<Edge>> &getEdges() const { return edges; }

  void setX(float new_x) { position.x = new_x; }
  void setY(float new_y) { position.y = new_y; }
  void setId(int _id) { id = _id; }
  void setName(std::string new_name) { name = new_name; }
  void setSelected(bool is_selected) { selected = is_selected; }

  void setPosition(float new_x, float new_y) {
    position.x = new_x;
    position.y = new_y;
  }

  bool contains(float x, float y, int radius) const {
    return std::pow(x - position.x, 2) + std::pow(y - position.y, 2) <=
           std::pow(radius, 2);
  }

  void addEdge(std::shared_ptr<Edge> edge);
  void removeEdge(const std::shared_ptr<Edge> &edge);

  void draw(SDL_Renderer *renderer, int radius,
            std::shared_ptr<BitmapFont> _font) const;
  bool isClicked(float mouseX, float mouseY);

  bool operator==(const Node &other) const {
    return id == other.getId() && position.x == other.getX() &&
           position.y == other.getY();
  }

private:
  int id;
  std::string name;
  bool selected;
  SDL_Point position;
  std::vector<std::shared_ptr<Edge>> edges;
};

#endif