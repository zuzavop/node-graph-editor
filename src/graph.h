#ifndef GRAPH_H
#define GRAPH_H

#include "edge.h"
#include "node.h"

class Graph {
public:
  Graph() {}

  void addNode(float x, float y);
  void addNode(const std::string &name, float x, float y);
  void addNode(std::shared_ptr<Node> node);
  void removeNode(const std::shared_ptr<Node> &node); 

  void addEdge(
      const std::shared_ptr<Node> &from,
      const std::shared_ptr<Node> &to); 
  void addEdge(std::shared_ptr<Edge> edge);
  void removeEdge(
      const std::shared_ptr<Edge> &edge);

  void draw(SDL_Renderer *renderer);
  void clearGraph();

  const std::vector<std::shared_ptr<Node>> &getNodes() const { return nodes; }

  const std::vector<std::shared_ptr<Edge>> &getEdges() const { return edges; }

  void saveToFile(const std::string &fileName);
  void loadFromFile(const std::string &fileName);
  void loadFromPSFile(const std::string &fileName);
  void exportToPSFile(const std::string &fileName);

  std::shared_ptr<Node> findNodeByPosition(float x, float y);
  std::shared_ptr<Node> findNodeByName(const std::string &name);
  std::shared_ptr<Node> findNodeById(int id);

private:
  std::vector<std::shared_ptr<Node>> nodes; // list of nodes in the graph
  std::vector<std::shared_ptr<Edge>> edges; // list of edges in the graph
};

#endif
