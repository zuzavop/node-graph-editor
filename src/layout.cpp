#include "layout.h"

double Layout::distance(double dx, double dy)
{
    return std::sqrt(dx * dx + dy * dy);
}

void Layout::layout(const std::unique_ptr<Graph> &graph, int width, int height,
                    int x, int y) {
  // use brute force layout for small graphs
  if (graph->getEdges().size() < 6) {
    layoutBruteForce(graph, width, height, 10, x, y);
  }
  // use Fruchterman-Reingold algorithm for large graphs
  else {
    fruchtermanReingold(graph, ITERATION, K, width, height, x, y);
  }
}

void Layout::fruchtermanReingold(const std::unique_ptr<Graph> &graph,
                                 int iterations, double k, int width, int height,
                                 int x, int y) {
  std::vector<std::pair<double, double>> pos(graph->getNodes().size());
  // initialize node positions to circle
  double angle = 2.0 * M_PI / graph->getNodes().size();
  for (int i = 0; i < graph->getNodes().size(); ++i) {
    pos[i].first = cos(i * angle) * (width / 2.0);
    pos[i].second = sin(i * angle) * (height / 2.0);
    graph->getNodes()[i]->setId(i + 1);
  }

  // set initial temperature and cooling factor
  double temperature = 10 * std::sqrt(graph->getNodes().size());
  double optimal_distance =
      k * std::sqrt((static_cast<unsigned long long>(width) * height) / graph->getNodes().size());
  bool stable = false;

  for (int iter = 0; iter < iterations && !stable; ++iter) {
    // repulsive forces between nodes
    std::vector<std::pair<double, double>> disp(graph->getNodes().size(),
                                              {0.0f, 0.0f});
    for (std::size_t i = 0; i < graph->getNodes().size() - 1; ++i) {
      for (std::size_t j = i + 1; j < graph->getNodes().size(); ++j) {
        double dx = pos[i].first - pos[j].first;
        double dy = pos[i].second - pos[j].second;
        double dist = std::max<double>(distance(dx, dy), E);
        if (dist > 1000.0) continue;
        double factor = optimal_distance * optimal_distance / dist;
        disp[i].first += (dx / dist) * factor;
        disp[i].second += (dy / dist) * factor;
        disp[j].first -= (dx / dist) * factor;
        disp[j].second -= (dy / dist) * factor;
      }
    }

    // attractive forces between edges
    for (const auto &e : graph->getEdges()) {
      int i = e->getSource()->getId() - 1;
      int j = e->getTarget()->getId() - 1;
      double dx = pos[i].first - pos[j].first;
      double dy = pos[i].second - pos[j].second;
      double dist = distance(dx, dy);
      if (dist <= E) continue;
      double factor = (dist * dist) / optimal_distance;
      disp[i].first -= (dx / dist) * factor;
      disp[i].second -= (dy / dist) * factor;
      disp[j].first += (dx / dist) * factor;
      disp[j].second += (dy / dist) * factor;
    }

    stable = true;
    // set nodes according to forces and temperature
    for (std::size_t i = 0; i < graph->getNodes().size(); ++i) {
      double dist = distance(pos[i].first, pos[i].second);
      if (dist > 1.0) stable = false;
      double factor = std::min<double>(dist, temperature);

      pos[i].first += pos[i].first / dist * factor;
      pos[i].second += pos[i].second / dist * factor;
    }

    if (temperature > 1.5)
      temperature *= COOLING_FACTOR;
    else
      temperature = 1.5;
  }
  // set final node positions
  for (int i = 0; i < graph->getNodes().size(); ++i) {
    graph->getNodes()[i]->setPosition((float)(pos[i].first + (width / 2)), (float)(pos[i].second + (height / 2)));
  }

  layoutFix(graph, width, height, x, y);
}

void Layout::layoutBruteForce(const std::unique_ptr<Graph> &graph, int width,
                              int height, int iterations, int x, int y) {
  // assign random coordinates to each node
  double angle = 2.0 * M_PI / graph->getNodes().size();
  std::size_t i = 0;
  for (const auto &n : graph->getNodes()) {
    double p_x = cos(i * angle) * (width / 2.0);
    double p_y = sin(i * angle) * (height / 2.0);
    n->setPosition(p_x + (width / 2.0), p_y + (height / 2.0));
    ++i;
  }

  // adjust node positions based on connections
  for (int i = 0; i < iterations; ++i) {
    for (const auto &edge : graph->getEdges()) {
      double dx = edge->getTarget()->getX() - edge->getSource()->getX();
      double dy = edge->getTarget()->getY() - edge->getSource()->getY();
      double d = distance(dx, dy);
      double ddx = dx / d;
      double ddy = dy / d;
      edge->getSource()->setPosition(edge->getSource()->getX() + ddx,
                                     edge->getSource()->getY() + ddy);
      edge->getTarget()->setPosition(edge->getTarget()->getX() - ddx,
                                     edge->getTarget()->getY() - ddy);
    }
  }

  layoutFix(graph, width, height, x, y);
}

void Layout::layoutFix(const std::unique_ptr<Graph> &graph, int width,
                       int height, int x, int y) {
  // normalize node positions to fit within the layout bounds
  double min_x = std::numeric_limits<double>::max();
  double max_x = std::numeric_limits<double>::min();
  double min_y = std::numeric_limits<double>::max();
  double max_y = std::numeric_limits<double>::min();
  for (const auto &node : graph->getNodes()) {
    min_x = std::min(min_x, node->getX());
    max_x = std::max(max_x, node->getX());
    min_y = std::min(min_y, node->getY());
    max_y = std::max(max_y, node->getY());
  }

  double scale_x = width / (max_x - min_x);
  double scale_y = height / (max_y - min_y);
  for (const auto &node : graph->getNodes()) {
    node->setPosition((!std::isnan(scale_x) && !std::isinf(scale_x) ? ((node->getX() - min_x) * scale_x) : (width / 2.0)) + x,
                      (!std::isnan(scale_y) && !std::isinf(scale_y) ? ((node->getY() - min_y) * scale_y) : (height / 2.0)) + y);
  }
}
