#include "layout.h"

float Layout::distance(float dx, float dy)
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
                                 int iterations, float k, double width, double height,
                                 int x, int y) {
  std::vector<std::pair<float, float>> pos(graph->getNodes().size());
  // initialize node positions to circle
  double angle = 2.0 * M_PI / graph->getNodes().size();
  for (std::size_t i = 0; i < graph->getNodes().size(); i++) {
    pos[i].first = cos(i * angle) * (width / 2);
    pos[i].second = sin(i * angle) * (height / 2);
    graph->getNodes()[i]->setId(i + 1);
  }

  // set initial temperature and cooling factor
  float temperature = 10 * std::sqrt(graph->getNodes().size());
  double optimal_distance =
      k * std::sqrt((width * height) / graph->getNodes().size());
  bool stable = false;

  for (int iter = 0; iter < iterations && !stable; ++iter) {
    // repulsive forces between nodes
    std::vector<std::pair<float, float>> disp(graph->getNodes().size(),
                                              {0.0f, 0.0f});
    for (std::size_t i = 0; i < graph->getNodes().size() - 1; i++) {
      for (std::size_t j = i + 1; j < graph->getNodes().size(); j++) {
        float dx = pos[i].first - pos[j].first;
        float dy = pos[i].second - pos[j].second;
        float dist = std::max<float>(distance(dx, dy), E);
        if (dist > 1000.0) continue;
        float factor = optimal_distance * optimal_distance / dist;
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
      float dx = pos[i].first - pos[j].first;
      float dy = pos[i].second - pos[j].second;
      float dist = distance(dx, dy);
      if (dist <= E) continue;
      float factor = (dist * dist) / optimal_distance;
      disp[i].first -= (dx / dist) * factor;
      disp[i].second -= (dy / dist) * factor;
      disp[j].first += (dx / dist) * factor;
      disp[j].second += (dy / dist) * factor;
    }

    stable = true;
    // set nodes according to forces and temperature
    for (std::size_t i = 0; i < graph->getNodes().size(); i++) {
      float dist = distance(pos[i].first, pos[i].second);
      if (dist > 1.0) stable = false;
      float factor = std::min<float>(dist, temperature);

      pos[i].first += pos[i].first / dist * factor;
      pos[i].second += pos[i].second / dist * factor;
    }

    if (temperature > 1.5)
      temperature *= COOLING_FACTOR;
    else
      temperature = 1.5;
  }
  // set final node positions
  for (std::size_t i = 0; i < graph->getNodes().size(); i++) {
    graph->getNodes()[i]->setPosition(pos[i].first + (width / 2), pos[i].second + (height / 2));
  }

  layoutFix(graph, width, height, x, y);
}

void Layout::layoutBruteForce(const std::unique_ptr<Graph> &graph, int width,
                              int height, int iterations, int x, int y) {
  // assign random coordinates to each node
  double angle = 2.0 * M_PI / graph->getNodes().size();
  std::size_t i = 0;
  for (const auto &n : graph->getNodes()) {
    float p_x = cos(i * angle) * (width / 2);
    float p_y = sin(i * angle) * (height / 2);
    n->setPosition(p_x + (width / 2), p_y + (height / 2));
    ++i;
  }

  // adjust node positions based on connections
  for (int i = 0; i < iterations; i++) {
    for (const auto &edge : graph->getEdges()) {
      float dx = edge->getTarget()->getX() - edge->getSource()->getX();
      float dy = edge->getTarget()->getY() - edge->getSource()->getY();
      float d = distance(dx, dy);
      float ddx = dx / d;
      float ddy = dy / d;
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
  float min_x = std::numeric_limits<float>::max();
  float max_x = std::numeric_limits<float>::min();
  float min_y = std::numeric_limits<float>::max();
  float max_y = std::numeric_limits<float>::min();
  for (const auto &node : graph->getNodes()) {
    min_x = std::min(min_x, node->getX());
    max_x = std::max(max_x, node->getX());
    min_y = std::min(min_y, node->getY());
    max_y = std::max(max_y, node->getY());
  }

  float scale_x = width / (max_x - min_x);
  float scale_y = height / (max_y - min_y);
  for (const auto &node : graph->getNodes()) {
    node->setPosition((!std::isnan(scale_x) && !std::isinf(scale_x) ? ((node->getX() - min_x) * scale_x) : (width / 2)) + x,
                      (!std::isnan(scale_y) && !std::isinf(scale_y) ? ((node->getY() - min_y) * scale_y) : (height / 2)) + y);
  }
}
