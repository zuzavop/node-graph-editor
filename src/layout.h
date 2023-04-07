#ifndef LAYOUT_H
#define LAYOUT_H

#include <memory>
#include <random>
#include <vector>

class Graph;

class Layout {
public:
  Layout() {}

  void layout(std::shared_ptr<Graph> graph, int width, int height, int x,
              int y);
  void layoutFix(std::shared_ptr<Graph> graph, int width, int height, int x,
                 int y);

private:
  void fruchtermanReingold(std::shared_ptr<Graph> graph, int iterations,
                           float k, int width, int height, int x, int y);
  void layoutBruteForce(std::shared_ptr<Graph> graph, int width, int height,
                        int iterations, int x, int y);
};

#endif
