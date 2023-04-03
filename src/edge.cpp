#include "edge.h"
#include "node.h"

void Edge::draw(SDL_Renderer *renderer) const {
  // Draw the edge
  SDL_RenderDrawLine(renderer, startNode->getX(), startNode->getY(),
                     endNode->getX(), endNode->getY());
}