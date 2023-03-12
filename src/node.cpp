
void Node::draw(SDL_Renderer* renderer) {
    // Draw the node
    SDL_RenderDrawCircle(renderer, x, y, NODE_RADIUS);
}
    
void Node::addEdge(std::shared_ptr<Edge> edge) {
    edges.push_back(edge);
}

void Node::removeEdge(std::shared_ptr<Edge>& edge) {
    edges.erase(std::remove(edges.begin(), edges.end(), edge), edges.end());
}

bool Node::isClicked(float mouseX, float mouseY) {
    return x == mouseX && y == mouseY;
}