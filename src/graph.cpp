#include "graph.h"

Graph::Graph() {
    nodes = {{100, 100}, {200, 200}};
}

Graph::add_edge(int x, int y) {
    for (int i = 0; i < nodes.size(); i++) {
        int nodeX = nodes[i].x;
        int nodeY = nodes[i].y;
        int dx = x - nodeX;
        int dy = y - nodeY;
        if (dx * dx + dy * dy < NODE_RADIUS * NODE_RADIUS) {
            if (edges.empty()) {
                edges.push_back({i, i});
            } else {
                edges.back().end = i;
            }
            break;
        }
    }
}

Graph::delete_edge() {
    if (!edges.empty()) {
        edges.pop_back();
    }
}

Graph::add_node(int x, int y) {
    nodes.push_back({x, y});
}