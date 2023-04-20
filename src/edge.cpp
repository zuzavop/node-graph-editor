#include "edge.h"
#include "node.h"

void Edge::draw(SDL_Renderer *renderer) const {
  double startAngle = atan2(m_endNode->getY() - m_startNode->getY(),
                            m_endNode->getX() - m_startNode->getX());
  double endAngle = startAngle + M_PI;

  double startX = m_startNode->getX() + NODE_RADIUS * cos(startAngle);
  double startY = m_startNode->getY() + NODE_RADIUS * sin(startAngle);
  double endX = m_endNode->getX() + NODE_RADIUS * cos(endAngle);
  double endY = m_endNode->getY() + NODE_RADIUS * sin(endAngle);

  SDL_RenderDrawLine(renderer, (int)startX, (int)startY, (int)endX, (int)endY);
  if (m_oriented) {
    // calculate arrowhead points
    double angleDiff = M_PI / 6;
    double x1 = endX - NODE_RADIUS * cos(startAngle - angleDiff);
    double y1 = endY - NODE_RADIUS * sin(startAngle - angleDiff);
    double x2 = endX - NODE_RADIUS * cos(startAngle + angleDiff);
    double y2 = endY - NODE_RADIUS * sin(startAngle + angleDiff);

    SDL_RenderDrawLine(renderer, (int)endX, (int)endY, (int)x1, (int)y1);
    SDL_RenderDrawLine(renderer, (int)endX, (int)endY, (int)x2, (int)y2);
  }
}

void Edge::switchNodes() {
  m_oriented = true;
  m_startNode.swap(m_endNode);
}