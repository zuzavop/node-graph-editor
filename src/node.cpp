#include "node.h"
#include "edge.h"
#include "main_window.h"

void Node::draw(SDL_Renderer *renderer, int radius) {
  for (int i = -radius; i <= radius; i++) {
    for (int j = -radius; j <= radius; j++) {
      if (i * i + j * j <= radius * radius) {
        SDL_RenderDrawPoint(renderer, (int)(m_x + i), (int)(m_y + j));
      }
    }
  }
  if (!m_name.empty()) {
    MainWindow::getInstance().font->renderText((int)m_x, (int)m_y, m_name, renderer, 0.2);
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

bool Node::isClicked(double mouseX, double mouseY) {
  return contains(mouseX, mouseY, NODE_RADIUS);
}
