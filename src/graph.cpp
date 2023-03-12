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
                add_node(new Node(id, x, y));
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
