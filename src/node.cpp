#include "node.h"
#include "edge.h"

void Node::draw(SDL_Renderer *renderer, int radius,
                std::shared_ptr<BitmapFont> _font) const {
  for (int i = -radius; i <= radius; i++) {
    for (int j = -radius; j <= radius; j++) {
      if (i * i + j * j <= radius * radius) {
        SDL_RenderDrawPoint(renderer, position.x + i, position.y + j);
      }
    }
  }
  if (name != "") {
    _font->renderText(position.x, position.y, name, renderer, 0.2);
  }
}

void Node::addEdge(std::shared_ptr<Edge> edge) { edges.push_back(edge); }

void Node::removeEdge(const std::shared_ptr<Edge> &edge) {
  edges.erase(std::remove(edges.begin(), edges.end(), edge), edges.end());
}

bool Node::isClicked(float mouseX, float mouseY) {
  return contains(mouseX, mouseY, NODE_RADIUS);
}
