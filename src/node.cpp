#include "node.h"
#include "edge.h"

void Node::draw(SDL_Renderer *renderer, int radius,
                const std::shared_ptr<BitmapFont> &font) const {
  for (int i = -radius; i <= radius; i++) {
    for (int j = -radius; j <= radius; j++) {
      if (i * i + j * j <= radius * radius) {
        SDL_RenderDrawPoint(renderer, m_position.x + i, m_position.y + j);
      }
    }
  }
  if (m_name != "") {
    font->renderText(m_position.x, m_position.y, m_name, renderer, 0.2);
  }
}

void Node::addEdge(std::shared_ptr<Edge> edge) { m_edges.push_back(edge); }

void Node::removeEdge(const std::shared_ptr<Edge> &edge) {
  m_edges.erase(std::remove(m_edges.begin(), m_edges.end(), edge),
                m_edges.end());
}

bool Node::isClicked(float mouseX, float mouseY) {
  return contains(mouseX, mouseY, NODE_RADIUS);
}
