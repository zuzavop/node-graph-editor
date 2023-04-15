#ifndef LAYOUT_H
#define LAYOUT_H

#include "graph.h"

const int ITERATION = 300;
const float K = 0.1;
const float COOLING_FACTOR = 0.8;
const float E = 2 * NODE_RADIUS; // minimum distance

class Layout {
public:
  Layout() {}

  void layout(const std::unique_ptr<Graph> &graph, int width, int height,
                 int x, int y);
  void layoutFix(const std::unique_ptr<Graph> &graph, int width, int height,
                 int x, int y);

private:
  void fruchtermanReingold(const std::unique_ptr<Graph> &graph, int iterations,
                           float k, double width, double height, int x, int y);
  void layoutBruteForce(const std::unique_ptr<Graph> &graph, int width,
                        int height, int iterations, int x, int y);

  static float distance(float dx, float dy);
};

#endif
