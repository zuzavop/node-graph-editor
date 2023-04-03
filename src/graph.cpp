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
  // check if the edge already exists
  for (const auto &edge : edges) {
    if (*edge == Edge(from, to)) {
      return;
    }
  }

  auto edge = std::make_shared<Edge>(from, to);
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
  // Open the file for writing
  std::ofstream file(filename);
  if (file.is_open()) {
    // write the nodes
    for (const auto &node : nodes) {
      // Draw a circle for the node
      file << "\\node (" << node->getId() << ") {" << node->getName() << "} "
           << node->getX() << " " << node->getY() << "\n";
    }

    // Draw the edges
    for (const auto &edge : edges) {
      // Compute the positions of the nodes
      const float x1 = edge->getSource()->getX();
      const float y1 = edge->getSource()->getY();
      const float x2 = edge->getTarget()->getX();
      const float y2 = edge->getTarget()->getY();

      // Draw a line for the edge
      file << x1 << " " << y1 << " -- " << x2 << " " << y2 << "\n";
    }

    // Close the file
    file.close();
  } else {
    std::cerr << "Failed to open file: " << filename << std::endl;
  }
}

void Graph::loadFromFile(const std::string &filename) {
  // Open the file for reading
  std::ifstream file(filename);
  if (file.is_open()) {
    clearGraph();

    // Parse the node definitions
    std::string line;
    int num_line = 1;
    while (std::getline(file, line)) {
      std::smatch match;
      if (std::regex_match(line, match,
                           std::regex(R"(\\node \((\d+)\) \{(\w*)\} (\d+) (\d+))"))) {
        // Extract the node position and size from the command
	const int id = std::stoi(match[1]);
	std::string name;
	try {
		name = match[2];
	} catch (std::invalid_argument const& ex) {
		name = "";
	}
	const float x = std::stof(match[3]);
	const float y = std::stof(match[4]);
	
        // Create a new node and add it to the graph
        addNode(std::make_shared<Node>(name, x, y, id));
      }
      else if (std::regex_match(line, match,
                           std::regex(R"(\\node \((\d+)\) \{(\w*)\})"))) {
        // Extract the node position and size from the command
	const int id = std::stoi(match[1]);
	std::string name;
	try {
		name = match[2];
	} catch (std::invalid_argument const& ex) {
		name = "";
	}

        // Create a new node and add it to the graph
        addNode(std::make_shared<Node>(name, 0, 0, id));
      }

      // Check if the line is an edge command
      else if (std::regex_match(
                   line, match,
                   std::regex(R"(\((\d+)\) -- \((\d+)\))"))) {
        // Extract the positions of the source and destination nodes
        const int id1 = std::stoi(match[1]);
        const int id2 = std::stoi(match[2]);
	
        // Find the nodes corresponding to the source and destination
        // positions
        auto sourceNode = findNodeById(id1);
        auto destNode = findNodeById(id2);

        // Add a new edge to the graph
        addEdge(std::make_shared<Edge>(sourceNode, destNode));
      } else if (std::regex_match(
                   line, match,
                   std::regex(R"((\d+) (\d+) -- (\d+) (\d+))"))) {
        // Extract the positions of the source and destination nodes
        const float x1 = std::stof(match[1]);
        const float y1 = std::stof(match[2]);
        const float x2 = std::stof(match[3]);
        const float y2 = std::stof(match[4]);
	
        // Find the nodes corresponding to the source and destination
        // positions
        auto sourceNode = findNodeByPosition(x1, y1);
        auto destNode = findNodeByPosition(x2, y2);

        // Add a new edge to the graph
        addEdge(std::make_shared<Edge>(sourceNode, destNode));
      } else {
	std::cerr << "Invalid line " << num_line << std::endl;
	break;
      }
      ++num_line;
    }
    // Close the file
      file.close();
  } else {
    std::cerr << "Failed to open file: " << filename << std::endl;
  }
}

void Graph::exportToPSFile(const std::string &filename) {
  // Open the file for writing
  std::ofstream file(filename);
  if (file.is_open()) {
    // Write the PostScript header
    file << "%!PS-Adobe-2.0\n\n";

    // Set the font size
    const float fontSize = 10.0f;

    // Draw the nodes
    for (const auto &node : nodes) {
      // Compute the position of the node
      const float x = node->getX();
      const float y = node->getY();

      // Draw a circle for the node
      file << x << " " << y << " " << NODE_RADIUS << " 0 360 arc\n"
           << "closepath\n"
           << "stroke\n";
    }

    file << "0.5 setlinewidth\n";

    // Draw the edges
    for (const auto &edge : edges) {
      // Compute the positions of the nodes
      const float x1 = edge->getSource()->getX();
      const float y1 = edge->getSource()->getY();
      const float x2 = edge->getTarget()->getX();
      const float y2 = edge->getTarget()->getY();

      // Draw a line for the edge
      file << x1 << " " << y1 << " moveto " << x2 << " " << y2 << " lineto\n"
           << "stroke\n";
    }

    // Write the PostScript footer
    file << "\nshowpage\n";

    // Close the file
    file.close();
  } else {
    std::cerr << "Failed to open file: " << filename << std::endl;
  }
}

void Graph::loadFromPSFile(const std::string &filename) {
  // Open the file for reading
  std::ifstream file(filename);
  if (file.is_open()) {
    clearGraph();

    // Read the PostScript commands
    std::string line;
    while (std::getline(file, line)) {
      // Check if the line is a node command
      std::smatch match;
      if (std::regex_match(line, match,
                           std::regex(R"((\S+) (\S+) (\S+) 0 360 arc)"))) {
        // Extract the node position and size from the command
        const float x = std::stof(match[1]);
        const float y = std::stof(match[2]);

        // Create a new node and add it to the graph
        addNode(std::make_shared<Node>(x, y));
      }

      // Check if the line is an edge command
      else if (std::regex_match(
                   line, match,
                   std::regex(R"((\S+) (\S+) moveto (\S+) (\S+) lineto)"))) {
        // Extract the positions of the source and destination nodes
        const float x1 = std::stof(match[1]);
        const float y1 = std::stof(match[2]);
        const float x2 = std::stof(match[3]);
        const float y2 = std::stof(match[4]);

        // Find the nodes corresponding to the source and destination
        // positions
        auto sourceNode = findNodeByPosition(x1, y1);
        auto destNode = findNodeByPosition(x2, y2);

        // Add a new edge to the graph
        addEdge(std::make_shared<Edge>(sourceNode, destNode));
      }

      // Check if the line is a label command
      // else if (std::regex_match(line, match, std::regex(R"(\((.+)\) \S+ \S+
      // rmoveto)"))) {
      // Extract the label text
      // const std::string label = match[1];

      // Find the node corresponding to the label
      // auto node = findNodeByName(label);

      // Set the node's name to the label text
      // node->setName(label);
      //}
    }

    // Close the file
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
  auto it =
      std::find_if(nodes.begin(), nodes.end(), [=](std::shared_ptr<Node> &n) {
        return n->contains(x, y, NODE_RADIUS);
      });

  if (it != std::end(nodes)) {
    auto id = std::distance(nodes.begin(), it);
    return nodes[id];
  }

  return nullptr;
}

std::shared_ptr<Node> Graph::findNodeByName(const std::string &name) {
  auto it =
      std::find_if(nodes.begin(), nodes.end(), [=](std::shared_ptr<Node> &n) {
        return n->getName() == name;
      });

  if (it != std::end(nodes)) {
    auto id = std::distance(nodes.begin(), it);
    return nodes[id];
  }

  return nullptr;
}

std::shared_ptr<Node> Graph::findNodeById(int id) {
  auto it =
      std::find_if(nodes.begin(), nodes.end(), [=](std::shared_ptr<Node> &n) {
        return n->getId() == id;
      });

  if (it != std::end(nodes)) {
    auto id = std::distance(nodes.begin(), it);
    return nodes[id];
  }

  return nullptr;
}
