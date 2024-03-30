#ifndef TYPES_HPP
#define TYPES_HPP

#include <map>
#include <vector>

struct Edge
{
    unsigned int from, to;
    double weight;

    Edge(unsigned f, unsigned t, double w) : from(f < t ? f : t), to(f >= t ? f : t), weight(w){};
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

#endif