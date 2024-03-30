#ifndef TYPES_H
#define TYPES_H

#include <map>
#include <vector>

struct Node
{
    double x, y;
    unsigned int id;
};

struct Edge
{
    unsigned int from, to;
    double weight;
};

class AdjacencyMatrix
{
    std::map<unsigned int, std::map<unsigned int, double>> matrix;

public:
    AdjacencyMatrix() {};
    AdjacencyMatrix(std::vector<Edge>);
    double addEdge(unsigned int, unsigned int, double);
    double removeEdge(unsigned int, unsigned int);
    std::vector<Edge> adjacentNodes(unsigned int) const;
    int nodeDegree(unsigned int) const;
    // void removeEdge(const Node& from, const Node& to) {
    //     matrix[from.id].erase(to.id);
    //     matrix[to.id].erase(from.id);
    // }
};

#endif