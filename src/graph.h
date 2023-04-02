#ifndef GRAPH_H
#define GRAPH_H

#include "node.h"
#include "edge.h"
#include "layout.h"

class Graph {
    public:
        Graph() {}

        void addNode(float x, float y); // create a node and add it to the graph
        void addNode(const std::string& name, float x, float y);
        void addNode(std::shared_ptr<Node> node); // add a node to the graph
        void removeNode(const std::shared_ptr<Node>& node); //delete a node from the graph
        
        void addEdge(const std::shared_ptr<Node>& from, const std::shared_ptr<Node>& to);  // create an edge and add it to graph
        void addEdge(std::shared_ptr<Edge> edge); // add an edge to the graph
        void removeEdge(const std::shared_ptr<Edge>& edge); // delete an edge from the graph

        void draw(SDL_Renderer* renderer); // draw the entire graph
        void clearGraph();

        void layout();

        const std::vector<std::shared_ptr<Node>>& getNodes() const {
            return nodes;
        }

        const std::vector<std::shared_ptr<Edge>>& getEdges() const {
            return edges;
        }

        void saveToFile(const std::string& fileName);
        void loadFromFile(const std::string& fileName);
        std::shared_ptr<Node> findNodeByPosition(float x, float y);
        std::shared_ptr<Node> findNodeByName(const std::string& name);
    private:
        std::vector<std::shared_ptr<Node>> nodes; // list of nodes in the graph
        std::vector<std::shared_ptr<Edge>> edges; // list of edges in the graph

	void fruchtermanReingold(int iterations, float k);
        void layoutBruteForce();

};

#endif
