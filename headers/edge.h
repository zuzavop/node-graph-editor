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
       bool isOriented = true)
      : m_startNode(start), m_endNode(end), m_selected(false),
        m_oriented(isOriented) {}

  std::shared_ptr<Node> getSource() const { return m_startNode; }
  std::shared_ptr<Node> getTarget() const { return m_endNode; }
  bool isSelected() const { return m_selected; }
  bool isOriented() const { return m_oriented; }

  void setSelected(bool isSelected) { m_selected = isSelected; }
  void setOrientation(bool isOriented) { m_oriented = isOriented; }
  void switchNodes();

  void draw(SDL_Renderer *renderer) const;

private:
  std::shared_ptr<Node> m_startNode; // starting node of the edge
  std::shared_ptr<Node> m_endNode;   // ending node of the edge
  bool m_selected;
  bool m_oriented;
};

inline bool operator==(const Edge &lhs, const Edge &rhs) {
  return (lhs.getSource() == rhs.getSource() &&
          lhs.getTarget() == rhs.getTarget());
}
inline bool operator!=(const Edge &lhs, const Edge &rhs) {
  return !operator==(lhs, rhs);
}
inline bool operator<(const Edge &lhs, const Edge &rhs) {
  return (lhs.getSource() < rhs.getSource() &&
          lhs.getTarget() < rhs.getTarget())
}
inline bool operator>(const Edge &lhs, const Edge &rhs) {
  return operator<(rhs, lhs);
}
inline bool operator<=(const Edge &lhs, const Edge &rhs) {
  return !operator>(lhs, rhs);
}
inline bool operator>=(const Edge &lhs, const Edge &rhs) {
  return !operator<(lhs, rhs);
}

#endif
