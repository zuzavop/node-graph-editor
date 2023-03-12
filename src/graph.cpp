#include "graph.h"

Graph::Graph() {
    //nodes = {{100, 100}, {200, 200}};
}

void Graph::addNode(std::shared_ptr<Node> node) {
    nodes.emplace_back(node);
}

void Graph::add_node(int x, int y) {
    //nodes.push_back({x, y});
}

void Graph::add_edge(int x, int y) {
    for (int i = 0; i < nodes.size(); i++) {
        int nodeX = nodes[i]->x;
        int nodeY = nodes[i]->y;
        int dx = x - nodeX;
        int dy = y - nodeY;
        if (dx * dx + dy * dy < NODE_RADIUS * NODE_RADIUS) {
            if (edges.empty()) {
                // edges.push_back({i, i});
            } else {
                // edges.back().end = i;
            }
            break;
        }
    }
}

void Graph::delete_edge(std::unique_ptr<Edge> edge) {
    if (!edges.empty()) {
        edges.pop_back();
    }
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
    std::ofstream file(fileName);
    if (file.is_open()) {
        for (auto node : nodes) {
            file << "NODE " << node->getID() << " " << node->getX() << " " << node->getY() << "\n";
            for (auto edge : node->get_edges()) {
                file << "EDGE " << edge->getStart()->getID() << " " << edge->getEnd()->getID() << " " << edge->getWeight() << "\n";
            }
        }
        file.close();
    }
}

void Graph::loadFromFile(const std::string& fileName) {
    std::ifstream file(fileName);
    if (file.is_open()) {
        clearGraph();
        std::string line;
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string type;
            ss >> type;
            if (type == "NODE") {
                int id, x, y;
                ss >> id >> x >> y;
                addNode(x, y);
            }
            else if (type == "EDGE") {
                int startID, endID, weight;
                ss >> startID >> endID >> weight;
                Node* startNode = findNodeByID(startID);
                Node* endNode = findNodeByID(endID);
                if (startNode != nullptr && endNode != nullptr) {
                    addEdge(new Edge(startNode, endNode, weight));
                }
            }
        }
        file.close();
    }
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


