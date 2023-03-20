#include "node.h"
#include "edge.h"

void Node::draw(SDL_Renderer* renderer, int radius) const {
   const int32_t diameter = (radius * 2);

   int32_t rx = (radius - 1);
   int32_t ry = 0;
   int32_t tx = 1;
   int32_t ty = 1;
   int32_t error = (tx - diameter);

   while (rx >= ry)
   {
      //  Each of the following renders an octant of the circle
      SDL_RenderDrawPoint(renderer, x + rx, y - ry);
      SDL_RenderDrawPoint(renderer, x + rx, y + ry);
      SDL_RenderDrawPoint(renderer, x - rx, y - ry);
      SDL_RenderDrawPoint(renderer, x - rx, y + ry);
      SDL_RenderDrawPoint(renderer, x + ry, y - rx);
      SDL_RenderDrawPoint(renderer, x + ry, y + rx);
      SDL_RenderDrawPoint(renderer, x - ry, y - rx);
      SDL_RenderDrawPoint(renderer, x - ry, y + rx);

      if (error <= 0)
      {
         ++ry;
         error += ty;
         ty += 2;
      }

      if (error > 0)
      {
         --rx;
         tx += 2;
         error += (tx - diameter);
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
