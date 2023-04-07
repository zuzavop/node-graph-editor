#include "layout.h"
#include "graph.h"

void Layout::layout(std::shared_ptr<Graph> graph, int width, int height, int x,
                    int y) {
  // use brute force layout for small graphs
  if (graph->getEdges().size() < 5) {
    layoutBruteForce(graph, width, height, 100, x, y);
  }
  // use Fruchterman-Reingold algorithm for large graphs
  else {
    fruchtermanReingold(graph, 100, 1.0, width, height, x, y);
  }
}

void Layout::fruchtermanReingold(std::shared_ptr<Graph> graph, int iterations,
                                 float k, int width, int height, int x, int y) {
  std::vector<std::pair<float, float>> pos(graph->getNodes().size());
  // initialize node positions randomly
  std::default_random_engine generator;
  std::uniform_real_distribution<float> distribution(0, 1);
  for (int i = 0; i < graph->getNodes().size(); i++) {
    pos[i].first = distribution(generator) * width;
    pos[i].second = distribution(generator) * height;
    graph->getNodes()[i]->setId(i + 1);
  }

  // set initial temperature and cooling factor
  float temperature = std::max(width, height) / 10.0;
  float cooling_factor = pow(temperature, 1.0f / iterations);
  const float c = k * std::sqrt(1.0f / graph->getNodes().size());
  double optimal_distance =
      k * std::sqrt((width * height) / graph->getNodes().size());

  for (int iter = 0; iter < iterations; ++iter) {
    // repulsive forces between nodes
    std::vector<std::pair<float, float>> disp(graph->getNodes().size(),
                                              {0.0f, 0.0f});
    for (int i = 0; i < graph->getNodes().size(); i++) {
      for (int j = i + 1; j < graph->getNodes().size(); j++) {
        float dx = pos[i].first - pos[j].first;
        float dy = pos[i].second - pos[j].second;
        float dist = std::max(1.0f, sqrt(dx * dx + dy * dy));
        float factor = dist * dist / optimal_distance;
        disp[i].first += factor * dx / dist;
        disp[i].second += factor * dy / dist;
      }
    }
    // attractive forces between edges
    for (const auto &e : graph->getEdges()) {
      int i = e->getSource()->getId() - 1;
      int j = e->getTarget()->getId() - 1;
      float dx = pos[i].first - pos[j].first;
      float dy = pos[i].second - pos[j].second;
      float dist = std::max(1.0f, sqrt(dx * dx + dy * dy));
      float factor = dist * dist / optimal_distance;
      disp[i].first += factor * dx / dist;
      disp[i].second += factor * dy / dist;
      disp[j].first -= factor * dx / dist;
      disp[j].second -= factor * dy / dist;
    }

    // set nodes according to forces and temperature
    for (int i = 0; i < graph->getNodes().size(); i++) {
      float dx_sum = 0.0;
      float dy_sum = 0.0;
      for (int j = 0; j < graph->getNodes().size(); j++) {
        if (i != j) {
          float dx = pos[i].first - pos[j].first;
          float dy = pos[i].second - pos[j].second;
          float dist = std::max(1.0f, sqrt(dx * dx + dy * dy));
          float factor = dist * dist / optimal_distance;
          float dx_sum = factor * dx / dist;
          float dy_sum = factor * dy / dist;
        }
      }
      pos[i].first += c * dx_sum;
      pos[i].second += c * dy_sum;
      pos[i].first = std::max<float>(0.0, std::min<float>(pos[i].first, width));
      pos[i].second =
          std::max<float>(0.0, std::min<float>(pos[i].second, height));
    }

    temperature *= cooling_factor;
  }
  // set final node positions
  for (int i = 0; i < graph->getNodes().size(); i++) {
    graph->getNodes()[i]->setPosition(pos[i].first + x, pos[i].second + y);
  }

  layoutFix(graph, width, height, x, y);
}

void Layout::layoutBruteForce(std::shared_ptr<Graph> graph, int width,
                              int height, int iterations, int x, int y) {
  // assign random coordinates to each node
  std::default_random_engine generator;
  std::uniform_real_distribution<float> distribution(0, 1);
  for (const auto &n : graph->getNodes()) {
    n->setPosition(distribution(generator) * width,
                   distribution(generator) * height);
  }

  // adjust node positions based on connections
  for (int i = 0; i < iterations; i++) {
    for (const auto &edge : graph->getEdges()) {
      float dx = edge->getTarget()->getX() - edge->getSource()->getX();
      float dy = edge->getTarget()->getY() - edge->getSource()->getY();
      float d = std::max(1.0f, std::sqrt(dx * dx + dy * dy));
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

void Layout::layoutFix(std::shared_ptr<Graph> graph, int width, int height,
                       int x, int y) {
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
    node->setPosition((node->getX() - min_x) * scale_x + x,
                      (node->getY() - min_y) * scale_y + y);
  }
}
