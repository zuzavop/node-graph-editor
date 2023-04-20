#include "graph.h"

void Graph::saveToFile(std::ofstream &file) {
  if (file.is_open()) {
    // write the nodes
    for (const auto &node : m_nodes) {
      file << "\\node (" << node->getId() << ") {" << node->getName() << "} "
           << node->getX() << " " << node->getY() << "\n";
    }

    // write the edges
    for (const auto &edge : m_edges) {

      if (edge->getSource()->getId() > 0 && edge->getTarget()->getId() > 0) {
        file << "(" << edge->getSource()->getId()
             << (edge->isOriented() ? ") --> (" : ") -- (")
             << edge->getTarget()->getId() << ")\n";
      } else {
        const double x1 = edge->getSource()->getX();
        const double y1 = edge->getSource()->getY();
        const double x2 = edge->getTarget()->getX();
        const double y2 = edge->getTarget()->getY();

        file << x1 << " " << y1 << (edge->isOriented() ? " --> " : " -- ") << x2
             << " " << y2 << "\n";
      }
    }
  }
}

void Graph::loadFromFile(std::ifstream &file) {
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
          m_needLayout = true;
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
  }
}

void Graph::exportToPSFile(std::ofstream &file) {
  if (file.is_open()) {
    // Calculate the scaling factor to fit the graph on a page
    const int padding = NODE_RADIUS * 2;
    double min_x = std::numeric_limits<double>::max();
    double max_x = std::numeric_limits<double>::min();
    double min_y = std::numeric_limits<double>::max();
    double max_y = std::numeric_limits<double>::min();
    for (const auto &node : m_nodes) {
      min_x = std::min(min_x, node->getX());
      max_x = std::max(max_x, node->getX());
      min_y = std::min(min_y, node->getY());
      max_y = std::max(max_y, node->getY());
    }

    const double width = max_x - min_x;
    const double height = max_y - min_y;
    const double scale_x = (A4_HEIGHT - (2 * padding)) / width;
    const double padding_x = padding - min_x;
    const double scale_y = (A4_WIDTH - (2 * padding)) / height;
    const double padding_y = padding - min_y;

    // Write the PostScript header
    file << "%!PS-Adobe-3.0" << std::endl
         << "%%BoundingBox: 0 0 " << A4_WIDTH << " " << A4_HEIGHT << std::endl
         << "%%EndComments\n" << std::endl;

    file << "/radius " << NODE_RADIUS << " def" << std::endl
         << "/Times-Roman findfont\n"
         << NODE_RADIUS << " scalefont\nsetfont\n" << std::endl;

    // Write the nodes to the file
    for (auto &node : m_nodes) {
      const auto x = (node->getX() + padding_x) * scale_x;
      const auto y = (node->getY() + padding_y) * scale_y;
      file << "newpath" << std::endl
           << y << " " << x << " radius 0 360 arc" << std::endl
           << "gsave\n  1 setgray\n  fill\ngrestore" << std::endl
           << "stroke\n" << std::endl;

      if (node->getName() != "") {
        file << "newpath" << std::endl
             << y + (NODE_RADIUS / 2) << " " << x - (3 * NODE_RADIUS / 4)
             << " moveto" << std::endl
             << "90 rotate" << std::endl
             << "(" << node->getName() << ") show" << std::endl
             << "-90 rotate\n" << std::endl;
      }
    }

    // Write the edges to the file
    for (auto &edge : m_edges) {
      double startAngle =
          atan2(edge->getTarget()->getY() - edge->getSource()->getY(),
                edge->getTarget()->getX() - edge->getSource()->getX());
      double endAngle = startAngle + M_PI;

      double fromX = (edge->getSource()->getX() + padding_x) * scale_x +
                  NODE_RADIUS * cos(startAngle);
      double fromY = (edge->getSource()->getY() + padding_y) * scale_y +
                  NODE_RADIUS * sin(startAngle);
      double toX = (edge->getTarget()->getX() + padding_x) * scale_x +
                NODE_RADIUS * cos(endAngle);
      double toY = (edge->getTarget()->getY() + padding_y) * scale_y +
                NODE_RADIUS * sin(endAngle);
      file << "newpath" << std::endl
           << fromY << " " << fromX << " moveto" << std::endl
           << toY << " " << toX << " lineto" << std::endl
           << "stroke\n" << std::endl;

      if (edge->isOriented()) {
        // calculate arrowhead points
        double x1 = toX - NODE_RADIUS * cos(startAngle - M_PI / 6);
        double y1 = toY - NODE_RADIUS * sin(startAngle - M_PI / 6);
        double x2 = toX - NODE_RADIUS * cos(startAngle + M_PI / 6);
        double y2 = toY - NODE_RADIUS * sin(startAngle + M_PI / 6);
        file << "newpath" << std::endl
             << y1 << " " << x1 << " moveto" << std::endl
             << toY << " " << toX << " lineto" << std::endl
             << y2 << " " << x2 << " lineto" << std::endl
             << "fill\n" << std::endl;
      }
    }

    // write the PostScript footer
    file << "\nshowpage\n";
  }
}

void Graph::loadFromPSFile(std::ifstream &file) {
  if (file.is_open()) {
    clearGraph();
    m_needLayout = true;

    // read the PostScript commands
    std::string line;
    while (std::getline(file, line)) {
      // Check if the line is a node command
      std::smatch match;

      if (std::regex_match(line, match,
                           std::regex(R"((\S+) (\S+) (\S+) 0 360 arc)"))) {
        const float y = std::stof(match[1]);
        const float x = std::stof(match[2]);

        addNode(std::make_shared<Node>(x, y));

        // skip the rest of the node command
        while (std::getline(file, line) && line.find("stroke") == std::string::npos &&
              line != "" && line.find("newpath") == std::string::npos) {
        }
      }
      // Check if the line is an edge command or name
      else if (std::regex_match(line, match,
                                std::regex(R"((\S+) (\S+) moveto)"))) {
        const float y1 = std::stof(match[1]);
        const float x1 = std::stof(match[2]);

        if (std::getline(file, line)) {
          if (std::regex_match(line, match,
                               std::regex(R"((\S+) (\S+) lineto)"))) {
            const float y2 = std::stof(match[1]);
            const float x2 = std::stof(match[2]);

            auto sourceNode = findNodeByPosition(x1, y1);
            auto destNode = findNodeByPosition(x2, y2);

            if (std::getline(file, line)) {
              if (std::regex_match(line, match,
                                   std::regex(R"((\S+) (\S+) lineto)"))) {
                if (!m_edges.empty() && m_edges.back()) {
                    m_edges.back()->setOrientation(true);
                }
              } else {
                if (sourceNode && destNode) {
                  addEdge(std::make_shared<Edge>(sourceNode, destNode, false));
                }
              }
            }
          } else {
            while (std::getline(file, line) &&
               !std::regex_match(line, match, std::regex(R"(\((\w*)\) show)")) &&
               line.find("newpath") == std::string::npos && line.find("stroke") == std::string::npos) {
            }
            
            if (match.size() > 0 && match[1].matched) {
              auto node = findNodeByPosition(x1, y1);
              if (node) {
                node->setName(match[1]);
              }
            }
          }
        }
      }
    }
  }
}
