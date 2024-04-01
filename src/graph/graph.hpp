#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "utils.hpp"

class Graph
{
    std::map<int, std::map<int, double>> matrix;

public:
    Graph(){};
    Graph(std::map<int, std::map<int, double>> newMatrix) : matrix(newMatrix){};
    static double tourCost(const std::vector<Edge>);
    void addEdge(int, int, double);
    void removeNode(int);
    void removeEdge(int, int);
    std::vector<Edge> getEdges() const;
    int nodeDegree(int);
    Graph exportMst() const;
    Graph exportCsf(const std::vector<int>) const;
};

#endif