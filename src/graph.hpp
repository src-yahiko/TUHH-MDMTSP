#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <map>
#include <set>
#include <vector>
struct Edge
{
    int from, to;
    double weight;

    Edge(int f, int t, double w) : from(std::min(f, t)), to(std::max(f, t)), weight(w) {}

    bool operator<(const Edge &other) const
    {
        if (weight == other.weight)
        {
            if (from == other.from)
                return to < other.to;
            return from < other.from;
        }
        return weight < other.weight;
    }
};
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
    Graph exportMst() const;
    Graph exportCsf(const std::vector<int>) const;
};

class UnionFind
{
public:
    std::map<int, int> parent;
    std::map<int, int> rank;
    int find(int);
    void unite(int, int);
};

#endif