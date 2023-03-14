#include "node.h"
#include "edge.h"

void Node::draw(SDL_Renderer* renderer, int radius) const {
    SDL_RenderDrawPoint(renderer, x, y);
}
    
void Node::addEdge(std::shared_ptr<Edge> edge) {
    edges.push_back(edge);
}

void Node::removeEdge(const std::shared_ptr<Edge>& edge) {
    edges.erase(std::remove(edges.begin(), edges.end(), edge), edges.end());
}

bool Node::isClicked(float mouseX, float mouseY) {
    return contains(mouseX, mouseY, NODE_RADIUS);
}