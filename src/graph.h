#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <algorithm>
#include <iostream>
#include <memory>
#include "node.h"
#include "edge.h"

class Graph {
    public:
        Graph();
        virtual ~Graph();

        void addNode(int x, int y); // create a node and add it to the graph
        void addNode(std::shared_ptr<Node> node); // add a node to the graph
        void removeNode(std::shared_ptr<Node> node); //delete a node from the graph
        
        void addEdge(std::shared_ptr<Node> first, std::shared_ptr<Node> second);  // create an edge and add it to graph
        void addEdge(std::shared_ptr<Edge> edge); // add an edge to the graph
        void deleteEdge(std::shared_ptr<Edge> edge); // delete an edge from the graph

        void draw(SDL_Renderer* renderer); // draw the entire graph
        void clearGraph();

        void layout(int iterations, float k);
        void fruchtermanReingold(int iterations, float k);
        void layoutBruteForce();

        const std::vector<std::shared_ptr<Node>>& getNodes() const {
            return nodes;
        }

        const std::vector<std::shared_ptr<Edge>>& getEdges() const {
            return edges;
        }

        void saveToFile(const std::string& fileName);
        void loadFromFile(const std::string& fileName);
    private:
        std::vector<std::shared_ptr<Node>> nodes; // list of nodes in the graph
        std::vector<std::shared_ptr<Edge>> edges; // list of edges in the graph
};

#endif