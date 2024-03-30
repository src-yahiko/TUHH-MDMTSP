#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "types.hpp"
#include <set>

class Graph
{
    std::set<unsigned int> nodes;
    std::vector<Edge> edges;
    AdjacencyMatrix matrix;

public:
    bool nodeExists(unsigned int) const;
    void addNode(unsigned int);
    void removeNode(unsigned int);
    void addNodes(const std::vector<unsigned int>);
    void removeNodes(const std::vector<unsigned int>);
    void addEdge(unsigned int, unsigned int, double);
    void removeEdge(unsigned int, unsigned int, double);
    void addEdges(const std::vector<Edge>);
    void removeEdges(const std::vector<Edge>);
    std::vector<unsigned int> getNodes() const;
    std::vector<Edge> getEdges() const;

};

#endif