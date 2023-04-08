#include "graph.h"

void Graph::addNode(const std::string &name, float x, float y) {
  m_nodes.push_back(std::make_shared<Node>(name, x, y));
}

void Graph::addNode(std::shared_ptr<Node> node) { m_nodes.push_back(node); }

void Graph::addNode(float x, float y) {
  m_nodes.push_back(std::make_shared<Node>("", x, y));
}

void Graph::removeNode(const std::shared_ptr<Node> &node) {
  // remove all edges connected to this node
  for (const auto &edge : node->getEdges()) {
    auto otherNode =
        edge->getSource() == node ? edge->getTarget() : edge->getSource();
    otherNode->removeEdge(edge);
    m_edges.erase(std::remove(m_edges.begin(), m_edges.end(), edge), m_edges.end());
  }

  m_nodes.erase(std::remove(m_nodes.begin(), m_nodes.end(), node), m_nodes.end());
}

void Graph::addEdge(const std::shared_ptr<Node> &from,
                    const std::shared_ptr<Node> &to) {
  auto edge = std::make_shared<Edge>(from, to);
  auto invertedEdge = std::make_shared<Edge>(to, from);
  // check if the edge already exists
  for (const auto &e : m_edges) {
    if (*e == *edge) {
      if (!e->isOriented()) {
        e->setOrientation(true);
      }
      e->setSelected(true);
      return;
    }
    if (*e == *invertedEdge) {
      if (e->isOriented()) {
        e->setOrientation(false);
      } else {
        e->switchNodes();
      }
      e->setSelected(true);
      return;
    }
  }

  edge->setSelected(true);
  from->addEdge(edge);
  to->addEdge(edge);
  m_edges.push_back(edge);
}

void Graph::addEdge(std::shared_ptr<Edge> edge) {
  // check if the edge already exists
  for (const auto &e : m_edges) {
    if (*e == *edge) {
      e->setSelected(true);
      return;
    }
  }

  edge->setSelected(true);
  m_edges.push_back(edge);
}

void Graph::removeEdge(const std::shared_ptr<Edge> &edge) {
  edge->getSource()->removeEdge(edge);
  edge->getTarget()->removeEdge(edge);
  m_edges.erase(std::remove(m_edges.begin(), m_edges.end(), edge), m_edges.end());
}

void Graph::draw(SDL_Renderer *renderer, std::shared_ptr<BitmapFont> m_font) {
  SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
  // draw all edges first
  for (auto edge : m_edges) {
    edge->draw(renderer);
  }

  // draw all nodes on top of the edges
  for (auto node : m_nodes) {
    node->draw(renderer, NODE_RADIUS, m_font);
  }
}

void Graph::clearGraph() {
  m_nodes.clear();
  m_edges.clear();
}

std::shared_ptr<Node> Graph::findNodeByPosition(float x, float y) {
  return findNode([&](std::shared_ptr<Node> &n) {
    return n->contains(x, y, NODE_RADIUS + 1);
  });
}

std::shared_ptr<Node> Graph::findNodeByName(std::string_view name) {
  return findNode(
      [&](std::shared_ptr<Node> &n) { return n->getName() == name; });
}

std::shared_ptr<Node> Graph::findNodeById(int id) {
  return findNode([&](std::shared_ptr<Node> &n) { return n->getId() == id; });
}

template <typename Func> std::shared_ptr<Node> Graph::findNode(Func func) {
  auto it = std::find_if(m_nodes.begin(), m_nodes.end(), func);

  if (it != std::end(m_nodes)) {
    auto id = std::distance(m_nodes.begin(), it);
    return m_nodes[id];
  }

  return nullptr;
}
