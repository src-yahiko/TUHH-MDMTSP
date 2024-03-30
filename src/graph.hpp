#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <map>
#include <set>
#include <vector>

struct Edge
{
    unsigned int from, to;
    double weight;

    Edge(unsigned f, unsigned t, double w) : from(f < t ? f : t), to(f >= t ? f : t), weight(w){};
    static bool compare(const Edge &lhs, const Edge &rhs)
    {
        return lhs.weight < rhs.weight;
    }
};

class UnionFind
{
    std::map<unsigned int, unsigned int> parent;
    std::map<unsigned int, unsigned int> rank;

public:
    void makeSet(unsigned int);
    unsigned int find(unsigned int);
    void unionSet(unsigned int, unsigned int);
};

class AdjacencyMatrix
{
    std::map<unsigned int, std::map<unsigned int, double>> matrix;

public:
    AdjacencyMatrix(){};
    AdjacencyMatrix(std::vector<Edge>);
    void addEdge(unsigned int, unsigned int, double);
    void removeEdge(unsigned int, unsigned int);
    std::vector<Edge> getEdgesOf(unsigned int) const;
    unsigned int getDegreeOf(unsigned int) const;
    double getWeightOf(unsigned int, unsigned int) const;
};
class Graph
{
    std::set<unsigned int> nodes;
    std::vector<Edge> edges;
    AdjacencyMatrix matrix;

public:
    Graph();
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
    void toKruskalMST();
};

#endif