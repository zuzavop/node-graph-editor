#include "graph.h"

Graph::Graph() {
}

void Graph::addNode(const std::string& name, float x, float y) {
    nodes.push_back(std::make_shared<Node>(name, x, y));
}

void Graph::addNode(std::shared_ptr<Node> node) {
    nodes.push_back(node);
}

void Graph::addNode(float x, float y) {
    nodes.push_back(std::make_shared<Node>("", x, y));
}

void Graph::removeNode(const std::shared_ptr<Node>& node) {
    // remove all edges connected to this node
    for (const auto& edge : node->edges) {
        auto otherNode = edge->startNode == node ? edge->endNode : edge->startNode;
        otherNode->removeEdge(edge);
        edges.erase(std::remove(edges.begin(), edges.end(), edge), edges.end());
    }

    nodes.erase(std::remove(nodes.begin(), nodes.end(), node), nodes.end());
}

void Graph::addEdge(const std::shared_ptr<Node>& from, const std::shared_ptr<Node>& to) {
    // check if the edge already exists
    for (const auto& edge : edges) {
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
    for (const auto& e : edges) {
        if (*e == edge) {
            return;
        }
    }
    
    edges.push_back(edge);
}

void Graph::removeEdge(const std::shared_ptr<Edge>& edge) {
    edge->startNode->removeEdge(edge);
    edge->endNode->removeEdge(edge);
    edges.erase(std::remove(edges.begin(), edges.end(), edge), edges.end());
}

void Graph::draw(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    // draw all edges first
    for (auto edge : m_edges) {
        edge->draw(renderer);
    }

    // draw all nodes on top of the edges
    for (auto node : m_nodes) {
        node->draw(renderer);
    }
}


void Graph::saveToFile(const std::string& fileName) {
    // Open the file for writing
    std::ofstream file(filename);

    // Write the PostScript header
    file << "%!PS-Adobe-2.0\n\n";

    // Set up the scaling factors
    const float xScale = 500.0f;
    const float yScale = 500.0f;

    // Set the font size
    const float fontSize = 10.0f;

    // Draw the nodes
    for (const auto& node : nodes) {
        // Compute the position of the node
        const float x = node->getX() * xScale;
        const float y = node->getY() * yScale;

        // Draw a circle for the node
        file << x << " " << y << " " << NODE_RADIUS << " 0 360 arc\n"
             << "closepath\n"
             << "stroke\n";

        // Draw the label for the node
        file << "(" << node->getName() << ") "
             << "dup stringwidth pop 2 div neg " << fontSize / 2.0f << " rmoveto\n"
             << "show\n";
    }

    // Draw the edges
    for (const auto& edge : edges) {
        // Compute the positions of the nodes
        const float x1 = edge->getSourceNode()->getX() * xScale;
        const float y1 = edge->getSourceNode()->getY() * yScale;
        const float x2 = edge->getDestNode()->getX() * xScale;
        const float y2 = edge->getDestNode()->getY() * yScale;

        // Draw a line for the edge
        file << x1 << " " << y1 << " moveto\n"
             << x2 << " " << y2 << " lineto\n"
             << "stroke\n";
    }

    // Write the PostScript footer
    file << "\nshowpage\n";

    // Close the file
    file.close();
}

void Graph::loadFromFile(const std::string& fileName) {
    // Open the file for reading
    std::ifstream file(filename);

    // Read the PostScript commands
    std::string line;
    while (std::getline(file, line)) {
        // Check if the line is a node command
        std::smatch match;
        if (std::regex_match(line, match, std::regex(R"((\S+) (\S+) (\S+) 0 360 arc)"))) {
            // Extract the node position and size from the command
            const float x = std::stof(match[1]);
            const float y = std::stof(match[2]);

            // Create a new node and add it to the graph
            addNode(std::make_shared<Node>(x, y));
        }

        // Check if the line is an edge command
        else if (std::regex_match(line, match, std::regex(R"((\S+) (\S+) moveto (\S+) (\S+) lineto)"))) {
            // Extract the positions of the source and destination nodes
            const float x1 = std::stof(match[1]);
            const float y1 = std::stof(match[2]);
            const float x2 = std::stof(match[3]);
            const float y2 = std::stof(match[4]);

            // Find the nodes corresponding to the source and destination positions
            auto sourceNode = findNodeByPosition(x1, y1);
            auto destNode = findNodeByPosition(x2, y2);

            // Add a new edge to the graph
            addEdge(std::make_shared<Edge>("", sourceNode, destNode));
        }

        // Check if the line is a label command
        else if (std::regex_match(line, match, std::regex(R"(\((.+)\) \S+ \S+ rmoveto)"))) {
            // Extract the label text
            const std::string label = match[1];

            // Find the node corresponding to the label
            auto node = findNodeByName(label);

            // Set the node's name to the label text
            node->setName(label);
        }
    }

    // Close the file
    file.close();
}

void Graph::layout(int iterations, float k) {
    // use brute force layout for small graphs
    if (m_nodes.size() < 10) {
        layoutBruteForce();
    }
    // use Fruchterman-Reingold algorithm for large graphs
    else {
        fruchtermanReingold(iterations, k);
    }
}

void Graph::fruchtermanReingold(int iterations, float k) {
    std::vector<std::pair<float, float>> pos(nodes.size());
    // initialize node positions randomly
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(0.0f, 1.0f);
    for (int i = 0; i < nodes.size(); i++) {
        pos[i].first = dist(gen);
        pos[i].second = dist(gen);
    }

    float t = 1.0f;
    const float deltaT = 1.0f / iterations;
    const float c = k * std::sqrt(1.0f / nodes.size());
    for (int iter = 0; iter < iterations; iter++) {
        // repulsive forces between nodes
        std::vector<std::pair<float, float>> disp(nodes.size(), {0.0f, 0.0f});
        for (int i = 0; i < nodes.size(); i++) {
            for (int j = i + 1; j < nodes.size(); j++) {
                float dx = pos[i].first - pos[j].first;
                float dy = pos[i].second - pos[j].second;
                float distSq = dx * dx + dy * dy;
                if (distSq > 0.0f) {
                    float factor = k * k / distSq;
                    disp[i].first += factor * dx;
                    disp[i].second += factor * dy;
                    disp[j].first -= factor * dx;
                    disp[j].second -= factor * dy;
                }
            }
        }
        // attractive forces between edges
        for (const auto& e : edges) {
            int i = e->getSource()->getIndex();
            int j = e->getDest()->getIndex();
            float dx = pos[i].first - pos[j].first;
            float dy = pos[i].second - pos[j].second;
            float dist = std::sqrt(dx * dx + dy * dy);
            float factor = dist * dist / k;
            disp[i].first -= factor * dx / dist;
            disp[i].second -= factor * dy / dist;
            disp[j].first += factor * dx / dist;
            disp[j].second += factor * dy / dist;
        }
        // limit maximum displacement per iteration
        for (int i = 0; i < nodes.size(); i++) {
            float dispLen = std::sqrt(disp[i].first * disp[i].first + disp[i].second * disp[i].second);
            if (dispLen > 0.0f) {
                float maxDisp = c * t;
                pos[i].first += disp[i].first / dispLen * std::min(dispLen, maxDisp);
                pos[i].second += disp[i].second / dispLen * std::min(dispLen, maxDisp);
            }
        }
        t -= deltaT;
    }
    // set final node positions
    for (int i = 0; i < nodes.size(); i++) {
        nodes[i]->setPosition(pos[i].first, pos[i].second);
    }
}

void Graph::layoutBruteForce() {
    // compute the size of the grid
    int gridSize = sqrt(nodes.size());

    // compute the node positions in a grid
    int index = 0;
    for (int row = 0; row < gridSize; row++) {
        for (int col = 0; col < gridSize; col++) {
            if (index < nodes.size()) {
                float x = static_cast<float>(col) / gridSize;
                float y = static_cast<float>(row) / gridSize;
                nodes[index]->setPosition(x, y);
                index++;
            }
        }
    }
}

void Graph::clearGraph() {
    nodes.clear();
    edges.clear();
}
