#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "utils.hpp"

class Graph
{

public:
    std::map<int, std::map<int, double>> matrix;
    Graph(){};
    Graph(std::map<int, std::map<int, double>> newMatrix) : matrix(newMatrix){};
    static double tourCost(const std::vector<Edge>);
    void addEdge(int, int, double);
    void removeNode(int);
    void removeEdge(int, int);
    double edgeWeight(int, int) const;
    static double edgeWeight(int, int, std::map<int, std::map<int, double>>);
    std::vector<Edge> getEdges() const;
    Graph exportMst() const;
    Graph exportCsf(const std::vector<int>) const;
    Graph exportRpp(std::map<int, std::map<int, double>>) const;
};

#endif