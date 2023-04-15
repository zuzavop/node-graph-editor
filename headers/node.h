#ifndef NODE_H
#define NODE_H

#include <algorithm>
#include <fstream>
#include <memory>
#include <random>
#include <regex>
#include <sstream>
#include <vector>

#include "text.h"

const int NODE_RADIUS = 8;

class Edge;

class Node {
public:
  Node(std::string name, float x, float y)
      : m_id(0), m_name(name), m_selected(false) {
    m_x = x;
    m_y = y;
  }

  Node(float x, float y) : m_id(0), m_name(""), m_selected(false) {
    m_x = x;
    m_y = y;
  }

  Node(std::string name, float x, float y, int id)
      : m_id(id), m_name(name), m_selected(false) {
    m_x = x;
    m_y = y;
  }

  float getX() const { return m_x; }
  float getY() const { return m_y; }
  int getId() const { return m_id; }
  bool isSelected() const { return m_selected; }
  const std::string getName() const { return m_name; }
  const std::vector<std::shared_ptr<Edge>> &getEdges() const { return m_edges; }

  void setX(float x) { m_x = x; }
  void setY(float y) { m_y = y; }
  void setId(int id) { m_id = id; }
  void setName(std::string name) { m_name = name; }
  void setSelected(bool isSelected) { m_selected = isSelected; }
  void setPosition(float x, float y) {
    m_x = x;
    m_y = y;
  }

  bool contains(float x, float y, int radius) const {
    return std::pow(x - m_x, 2) + std::pow(y - m_y, 2) <= std::pow(radius, 2);
  }

  void addEdge(std::shared_ptr<Edge> edge);
  void removeEdge(const std::shared_ptr<Edge> &edge);

  void draw(SDL_Renderer *renderer, int radius);
  bool isClicked(float mouseX, float mouseY);

private:
  int m_id;
  std::string m_name;
  bool m_selected;
  float m_x, m_y;
  std::vector<std::shared_ptr<Edge>> m_edges;
};

inline bool operator==(const Node &lhs, const Node &rhs) {
  return lhs.getId() == rhs.getId() && lhs.getX() == rhs.getX() &&
         lhs.getY() == rhs.getY();
}
inline bool operator!=(const Node &lhs, const Node &rhs) {
  return !operator==(lhs, rhs);
}
inline bool operator<(const Node &lhs, const Node &rhs) {
  return lhs.getId() > rhs.getId();
}
inline bool operator>(const Node &lhs, const Node &rhs) {
  return operator<(rhs, lhs);
}
inline bool operator<=(const Node &lhs, const Node &rhs) {
  return !operator>(lhs, rhs);
}
inline bool operator>=(const Node &lhs, const Node &rhs) {
  return !operator<(lhs, rhs);
}

#endif
