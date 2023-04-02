#include "layout.h"
#include "graph.h"

void Layout::layout(std::shared_ptr<Graph> graph, int width, int height) {
    // use brute force layout for small graphs
    if (graph->getNodes().size() < 5) {
        layoutBruteForce(graph);
    }
    // use Fruchterman-Reingold algorithm for large graphs
    else {
        fruchtermanReingold(graph, 100, 10, width, height);
    }
}

void Layout::fruchtermanReingold(std::shared_ptr<Graph> graph, int iterations, float k, int width, int height) {
    std::vector<std::pair<float, float>> pos(graph->getNodes().size());
    // initialize node positions randomly
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(0.0f, 1.0f);
    for (int i = 0; i < graph->getNodes().size(); i++) {
        pos[i].first = dist(gen);
        pos[i].second = dist(gen);
    }

    float t = 1.0f;
    const float deltaT = 1.0f / iterations;
    const float c = k * std::sqrt(1.0f / graph->getNodes().size());
    for (int iter = 0; iter < iterations; iter++) {
        // repulsive forces between nodes
        std::vector<std::pair<float, float>> disp(graph->getNodes().size(), {0.0f, 0.0f});
        for (int i = 0; i < graph->getNodes().size(); i++) {
            for (int j = i + 1; j < graph->getNodes().size(); j++) {
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
        for (const auto& e : graph->getEdges()) {
            int i = e->getSource()->getId();
            int j = e->getTarget()->getId();
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
        for (int i = 0; i < graph->getNodes().size(); i++) {
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
    for (int i = 0; i < graph->getNodes().size(); i++) {
        graph->getNodes()[i]->setPosition(pos[i].first + (width / 2), pos[i].second + (height / 2));
    }
}

void Layout::layoutBruteForce(std::shared_ptr<Graph> graph) {
    // compute the size of the grid
    int gridSize = sqrt(graph->getNodes().size());

    // compute the node positions in a grid
    for (const auto& n : graph->getNodes()) {
    	for (int row = 0; row < gridSize; row++) {
            for (int col = 0; col < gridSize; col++) {
            	float x = static_cast<float>(col) / gridSize;
                float y = static_cast<float>(row) / gridSize;
                n->setPosition(x, y);
            }
        }
    }
}

