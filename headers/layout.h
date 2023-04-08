#ifndef LAYOUT_H
#define LAYOUT_H

#include "graph.h"

const int ITERATION = 100;
const float K = 1.0;

class Layout {
public:
  Layout() {}

  void layout(const std::shared_ptr<Graph> &graph, int width, int height, int x,
              int y);
  void layoutFix(const std::shared_ptr<Graph> &graph, int width, int height,
                 int x, int y);

private:
  void fruchtermanReingold(const std::shared_ptr<Graph> &graph, int iterations,
                           float k, int width, int height, int x, int y);
  void layoutBruteForce(const std::shared_ptr<Graph> &graph, int width,
                        int height, int iterations, int x, int y);
};

#endif
