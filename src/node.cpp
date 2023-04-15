#include "node.h"
#include "edge.h"
#include "main_window.h"

void Node::draw(SDL_Renderer *renderer, int radius) {
  for (int i = -radius; i <= radius; i++) {
    for (int j = -radius; j <= radius; j++) {
      if (i * i + j * j <= radius * radius) {
        SDL_RenderDrawPoint(renderer, m_x + i, m_y + j);
      }
    }
  }
  if (!m_name.empty()) {
    MainWindow::getInstance().font->renderText(m_x, m_y, m_name, renderer, 0.2);
  }
}

void Node::addEdge(std::shared_ptr<Edge> edge) { 
  auto invertedEdge = std::make_shared<Edge>(edge->getTarget(), edge->getSource());
  for (const auto &e : m_edges) {
    if (*e == *edge || *e == *invertedEdge) {
      return;
    }
  }
  
  m_edges.push_back(edge); 
}

void Node::removeEdge(const std::shared_ptr<Edge> &edge) {
  m_edges.erase(std::remove(m_edges.begin(), m_edges.end(), edge),
                m_edges.end());
}

bool Node::isClicked(float mouseX, float mouseY) {
  return contains(mouseX, mouseY, NODE_RADIUS);
}
