#include "node.h"
#include "edge.h"

void Node::draw(SDL_Renderer* renderer, int radius) const {
   for (int i = 0; i < radius * 2; i++) {
        for (int j = 0; j < radius * 2; j++) {
            int dx = radius - i;
            int dy = radius - j;
            if ((dx*dx + dy*dy) <= (radius * radius)) {
                SDL_RenderDrawPoint(renderer, x + dx, y + dy);
            }
        }
    }
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
