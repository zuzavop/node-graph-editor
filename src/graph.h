
#ifndef GRAPH_H
#define GRAPH_H

const int NODE_RADIUS = 20;

// Define a structure for a graph node
struct Node {
    int x, y;
};

// Define a structure for a graph edge
struct Edge {
    int start, end;
};

class Graph {
    public:
        Graph();
        add_edge(int x, int y);
        delete_edge();
        add_node(int x, int y);
        std::vector<Node> nodes;
        std::vector<Edge> edges;
}

#endif