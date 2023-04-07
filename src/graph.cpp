#include "graph.h"

void Graph::addNode(const std::string &name, float x, float y) {
  nodes.push_back(std::make_shared<Node>(name, x, y));
}

void Graph::addNode(std::shared_ptr<Node> node) { nodes.push_back(node); }

void Graph::addNode(float x, float y) {
  nodes.push_back(std::make_shared<Node>("", x, y));
}

void Graph::removeNode(const std::shared_ptr<Node> &node) {
  // remove all edges connected to this node
  for (const auto &edge : node->getEdges()) {
    auto otherNode =
        edge->getSource() == node ? edge->getTarget() : edge->getSource();
    otherNode->removeEdge(edge);
    edges.erase(std::remove(edges.begin(), edges.end(), edge), edges.end());
  }

  nodes.erase(std::remove(nodes.begin(), nodes.end(), node), nodes.end());
}

void Graph::addEdge(const std::shared_ptr<Node> &from,
                    const std::shared_ptr<Node> &to) {
  auto edge = std::make_shared<Edge>(from, to);
  auto invertedEdge = std::make_shared<Edge>(to, from);
  // check if the edge already exists
  for (const auto &e : edges) {
    if (*e == *edge) {
      if (!e->isOriented()) {
        e->setOrientation(true);
      }
      return;
    }
    if (*e == *invertedEdge) {
      if (e->isOriented()) {
        e->setOrientation(false);
      } else {
        e->switchNodes();
      }
      return;
    }
  }

  from->addEdge(edge);
  to->addEdge(edge);
  edges.push_back(edge);
}

void Graph::addEdge(std::shared_ptr<Edge> edge) {
  // check if the edge already exists
  for (const auto &e : edges) {
    if (e == edge) {
      return;
    }
  }

  edges.push_back(edge);
}

void Graph::removeEdge(const std::shared_ptr<Edge> &edge) {
  edge->getSource()->removeEdge(edge);
  edge->getTarget()->removeEdge(edge);
  edges.erase(std::remove(edges.begin(), edges.end(), edge), edges.end());
}

void Graph::draw(SDL_Renderer *renderer) {
  SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
  // draw all edges first
  for (auto edge : edges) {
    edge->draw(renderer);
  }

  // draw all nodes on top of the edges
  for (auto node : nodes) {
    node->draw(renderer, NODE_RADIUS);
  }
}

void Graph::saveToFile(const std::string &filename) {
  // open the file for writing
  std::ofstream file(filename);

  if (file.is_open()) {
    // write the nodes
    for (const auto &node : nodes) {
      file << "\\node (" << node->getId() << ") {" << node->getName() << "} "
           << node->getX() << " " << node->getY() << "\n";
    }

    // write the edges
    for (const auto &edge : edges) {

      if (edge->getSource()->getId() > 0 && edge->getTarget()->getId() > 0) {
        file << "(" << edge->getSource()->getId()
             << (edge->isOriented() ? ") --> (" : ") -- (")
             << edge->getTarget()->getId() << ")\n";
      } else {
        const float x1 = edge->getSource()->getX();
        const float y1 = edge->getSource()->getY();
        const float x2 = edge->getTarget()->getX();
        const float y2 = edge->getTarget()->getY();

        file << x1 << " " << y1 << (edge->isOriented() ? " --> " : " -- ") << x2
             << " " << y2 << "\n";
      }
    }

    file.close();
  } else {
    std::cerr << "Failed to open file: " << filename << std::endl;
  }
}

void Graph::loadFromFile(const std::string &filename) {
  // open the file for reading
  std::ifstream file(filename);
  if (file.is_open()) {
    clearGraph();

    std::string line;
    int num_line = 1;

    // Define regex constants for node and edge parsing
    const std::regex node_regex(R"(\\node \((\d+)\) \{(\w*)\}( (\d+) (\d+))?)");
    const std::regex edge_regex(R"(\((\d+)\) (--|<--|-->) \((\d+)\))");
    const std::regex pos_edge_regex(R"((\d+) (\d+) (--|<--|-->) (\d+) (\d+))");

    while (std::getline(file, line)) {
      std::smatch match;
      // parse the node definitions
      if (std::regex_match(line, match, node_regex)) {
        const int id = std::stoi(match[1]);
        std::string name = match[2].matched ? match.str(2) : "";
        const float x = match[4].matched ? std::stof(match[4]) : 0;
        const float y = match[5].matched ? std::stof(match[5]) : 0;
        if (!match[4].matched || !match[5].matched) {
          _needLayout = true;
        }

        addNode(std::make_shared<Node>(name, x, y, id));
      } else if (std::regex_match(line, match, edge_regex)) {
        int id1 = std::stoi(match[1]);
        int id2 = std::stoi(match[3]);

        const std::string type = match[2];
        const bool directed = type == "-->" || type == "<--";
        if (type == "<--") {
          std::swap(id1, id2);
        }

        auto sourceNode = findNodeById(id1);
        auto destNode = findNodeById(id2);

        addEdge(std::make_shared<Edge>(sourceNode, destNode, directed));
      } else if (std::regex_match(line, match, pos_edge_regex)) {
        float x1 = std::stof(match[1]);
        float y1 = std::stof(match[2]);
        float x2 = std::stof(match[4]);
        float y2 = std::stof(match[5]);

        const std::string type = match[3];
        const bool directed = type == "-->" || type == "<--";
        if (type == "<--") {
          std::swap(x1, x2);
          std::swap(y1, y2);
        }

        auto sourceNode = findNodeByPosition(x1, y1);
        auto destNode = findNodeByPosition(x2, y2);

        addEdge(std::make_shared<Edge>(sourceNode, destNode, directed));
      } else if (line.size() > 0) {
        std::cerr << "Invalid line " << num_line << std::endl;
        break;
      }
      ++num_line;
    }
    file.close();
  } else {
    std::cerr << "Failed to open file: " << filename << std::endl;
  }
}

void Graph::exportToPSFile(const std::string &filename) {
  // open the file for writing
  std::ofstream file(filename);
  if (file.is_open()) {

    // Calculate the scaling factor to fit the graph on a page
    const float padding = NODE_RADIUS * 2;
    float min_x = std::numeric_limits<float>::max();
    float max_x = std::numeric_limits<float>::min();
    float min_y = std::numeric_limits<float>::max();
    float max_y = std::numeric_limits<float>::min();
    for (const auto &node : nodes) {
      min_x = std::min(min_x, node->getX());
      max_x = std::max(max_x, node->getX());
      min_y = std::min(min_y, node->getY());
      max_y = std::max(max_y, node->getY());
    }

    const float width = max_x - min_x;
    const float height = max_y - min_y;
    const float scale_x = (A4_HEIGHT - (2 * padding)) / width;
    const float padding_x = padding - min_x;
    const float scale_y = (A4_WIDTH - (2 * padding)) / height;
    const float padding_y = padding - min_y;

    // Write the PostScript header
    file << "%!PS-Adobe-3.0" << std::endl
         << "%%BoundingBox: 0 0 " << A4_WIDTH << " " << A4_HEIGHT << std::endl
         << "%%EndComments\n\n";
    file << "/radius " << NODE_RADIUS << " def" << std::endl;

    // Write the edges to the file
    for (auto &edge : edges) {
      const auto fromX = (edge->getSource()->getX() + padding_x) * scale_x;
      const auto fromY = (edge->getSource()->getY() + padding_y) * scale_y;
      const auto toX = (edge->getTarget()->getX() + padding_x) * scale_x;
      const auto toY = (edge->getTarget()->getY() + padding_y) * scale_y;
      file << fromY << " " << fromX << " moveto" << std::endl
           << toY << " " << toX << " lineto" << std::endl
           << "stroke\n"
           << std::endl;
    }

    // Write the nodes to the file
    for (auto &node : nodes) {
      const auto x = (node->getX() + padding_x) * scale_x;
      const auto y = (node->getY() + padding_y) * scale_y;
      file << y << " " << x << " radius 0 360 arc" << std::endl
           << "fill" << std::endl;
    }

    // write the PostScript footer
    file << "\nshowpage\n";

    file.close();
  } else {
    std::cerr << "Failed to open file: " << filename << std::endl;
  }
}

void Graph::loadFromPSFile(const std::string &filename) {
  // open the file for reading
  std::ifstream file(filename);
  if (file.is_open()) {
    clearGraph();

    // read the PostScript commands
    std::string line;
    while (std::getline(file, line)) {
      // Check if the line is a node command
      std::smatch match;
      if (std::regex_match(line, match,
                           std::regex(R"((\S+) (\S+) (\S+) 0 360 arc)"))) {
        const float x = std::stof(match[1]);
        const float y = std::stof(match[2]);

        addNode(std::make_shared<Node>(x, y));
      }

      // Check if the line is an edge command
      else if (std::regex_match(line, match,
                                std::regex(R"((\S+) (\S+) moveto)"))) {
        const float x1 = std::stof(match[1]);
        const float y1 = std::stof(match[2]);
        if (std::getline(file, line) &&
            std::regex_match(line, match,
                             std::regex(R"((\S+) (\S+) lineto)"))) {
          const float x2 = std::stof(match[1]);
          const float y2 = std::stof(match[2]);

          auto sourceNode = findNodeByPosition(x1, y1);
          auto destNode = findNodeByPosition(x2, y2);

          addEdge(std::make_shared<Edge>(sourceNode, destNode));
        }
      }
    }

    file.close();
  } else {
    std::cerr << "Failed to open file: " << filename << std::endl;
  }
}

void Graph::clearGraph() {
  nodes.clear();
  edges.clear();
}

std::shared_ptr<Node> Graph::findNodeByPosition(float x, float y) {
  return findNode(
      [&](std::shared_ptr<Node> &n) { return n->contains(x, y, NODE_RADIUS); });
}

std::shared_ptr<Node> Graph::findNodeByName(const std::string &name) {
  return findNode(
      [&](std::shared_ptr<Node> &n) { return n->getName() == name; });
}

std::shared_ptr<Node> Graph::findNodeById(int id) {
  return findNode([&](std::shared_ptr<Node> &n) { return n->getId() == id; });
}

template <typename Func> std::shared_ptr<Node> Graph::findNode(Func func) {
  auto it = std::find_if(nodes.begin(), nodes.end(), func);

  if (it != std::end(nodes)) {
    auto id = std::distance(nodes.begin(), it);
    return nodes[id];
  }

  return nullptr;
}
