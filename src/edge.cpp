
void Edge::draw(SDL_Renderer* renderer) {
    // Draw the edge
    SDL_RenderDrawLine(renderer, m_fromNode->m_x, m_fromNode->m_y, m_toNode->m_x, m_toNode->m_y);
}