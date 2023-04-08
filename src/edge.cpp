#include "edge.h"
#include "node.h"

void Edge::draw(SDL_Renderer *renderer) const {
  double startAngle = atan2(m_endNode->getY() - m_startNode->getY(),
                            m_endNode->getX() - m_startNode->getX());
  double endAngle = startAngle + M_PI;

  int startX = m_startNode->getX() + NODE_RADIUS * cos(startAngle);
  int startY = m_startNode->getY() + NODE_RADIUS * sin(startAngle);
  int endX = m_endNode->getX() + NODE_RADIUS * cos(endAngle);
  int endY = m_endNode->getY() + NODE_RADIUS * sin(endAngle);

  SDL_RenderDrawLine(renderer, startX, startY, endX, endY);
  if (m_oriented) {
    // calculate arrowhead points
    double x1 = endX - NODE_RADIUS * cos(startAngle - M_PI / 6);
    double y1 = endY - NODE_RADIUS * sin(startAngle - M_PI / 6);
    double x2 = endX - NODE_RADIUS * cos(startAngle + M_PI / 6);
    double y2 = endY - NODE_RADIUS * sin(startAngle + M_PI / 6);

    SDL_RenderDrawLine(renderer, endX, endY, (int)x1, (int)y1);
    SDL_RenderDrawLine(renderer, endX, endY, (int)x2, (int)y2);
  }
}

void Edge::switchNodes() {
  m_oriented = true;
  m_startNode.swap(m_endNode);
}