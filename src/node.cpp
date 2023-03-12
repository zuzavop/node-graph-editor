
void Node::draw(SDL_Renderer* renderer) {
    // Draw the node
    SDL_RenderDrawCircle(renderer, x, y, NODE_RADIUS);
}
    
void Node::addEdge(std::shared_ptr<Node> end, int weight) {
    edges.emplace_back(std::make_shared<Edge>(this, end.get(), weight));
    end->incomingEdges.emplace_back(m_edges.back());
}

void Node::removeEdge(std::shared_ptr<Node> end) {
    edges.erase(std::remove_if(edges.begin(), edges.end(),
        [end](const std::shared_ptr<Edge>& e) { return e->getEnd() == end.get(); }),
        edges.end());

    end->incomingEdges.erase(std::remove_if(end->incomingEdges.begin(), end->incomingEdges.end(),
        [this](const std::shared_ptr<Edge>& e) { return e->getStart() == this; }),
        end->incomingEdges.end());
}

bool Node::isClicked(int mouseX, int mouseY) {
    return x == mouseX && y == mouseY;
}