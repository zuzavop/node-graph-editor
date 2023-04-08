#ifndef GRAPH_H
#define GRAPH_H

#include "edge.h"
#include "node.h"

const int A4_WIDTH = 595;
const int A4_HEIGHT = 842;

class Graph {
public:
  Graph() {}

  void addNode(float x, float y);
  void addNode(const std::string &name, float x, float y);
  void addNode(std::shared_ptr<Node> node);
  void removeNode(const std::shared_ptr<Node> &node);

  void addEdge(const std::shared_ptr<Node> &from,
               const std::shared_ptr<Node> &to);
  void addEdge(std::shared_ptr<Edge> edge);
  void removeEdge(const std::shared_ptr<Edge> &edge);

  void draw(SDL_Renderer *renderer, std::shared_ptr<BitmapFont> _font);
  void clearGraph();

  const std::vector<std::shared_ptr<Node>> &getNodes() const { return nodes; }
  const std::vector<std::shared_ptr<Edge>> &getEdges() const { return edges; }

  void saveToFile(std::ofstream &file);
  void loadFromFile(std::ifstream &file);
  void loadFromPSFile(std::ifstream &file);
  void exportToPSFile(std::ofstream &file);

  std::shared_ptr<Node> findNodeByPosition(float x, float y);
  std::shared_ptr<Node> findNodeByName(const std::string &name);
  std::shared_ptr<Node> findNodeById(int id);

  bool needLayout() { return _needLayout; }
  void wasLayout() { _needLayout = false; }

private:
  std::vector<std::shared_ptr<Node>> nodes; // list of nodes in the graph
  std::vector<std::shared_ptr<Edge>> edges; // list of edges in the graph

  bool _needLayout;

  template <typename Func> std::shared_ptr<Node> findNode(Func func);
};

#endif
