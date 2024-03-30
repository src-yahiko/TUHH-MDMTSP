#include "types.h"

AdjacencyMatrix::AdjacencyMatrix(std::vector<Edge> edges)
{
    for (const auto &edge : edges)
        addEdge(edge.from, edge.to, edge.weight);
}

void AdjacencyMatrix::addEdge(unsigned int fromId, unsigned int toId, double weight)
{
    matrix[fromId][toId] = weight;
    matrix[toId][fromId] = weight;
}

void AdjacencyMatrix::removeEdge(unsigned int fromId, unsigned int toId)
{
    matrix[fromId].erase(toId);
    matrix[toId].erase(fromId);
}

std::vector<Edge> AdjacencyMatrix::getEdgesOf(unsigned int nodeId) const
{
    std::vector<Edge> edges;
    auto it = matrix.find(nodeId);
    if (it != matrix.end())
        for (const auto &adj : it->second)
            edges.emplace_back(nodeId, adj.first, adj.second);

    return edges;
}

unsigned int AdjacencyMatrix::getDegreeOf(unsigned int nodeId) const
{
    unsigned int size = 0;
    auto it = matrix.find(nodeId);
    if (it != matrix.end())
        size = (it->second).size();
    return size;
}

double AdjacencyMatrix::getWeightOf(unsigned int fromId, unsigned int toId) const
{
    auto fromIt = matrix.find(fromId);
    if (fromIt == matrix.end())
        return -1;
    
    auto toIt = fromIt->second.find(toId);
    if (toIt == fromIt->second.end())
        return -1;

    return toIt->second;
}