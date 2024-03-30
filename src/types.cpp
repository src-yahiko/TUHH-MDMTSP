#include "types.h"

AdjacencyMatrix::AdjacencyMatrix(std::vector<Edge> edges) {
    for (const auto& edge: edges)
        addEdge(edge.from, edge.to, edge.weight);
}

double AdjacencyMatrix::addEdge(unsigned int fromId, unsigned int toId, double weight) {
    matrix[fromId][toId] = weight;
    matrix[toId][fromId] = weight;
    return weight;
}

double AdjacencyMatrix::removeEdge(unsigned int fromId, unsigned int toId) {
    matrix[fromId].erase(toId);
    matrix[toId].erase(fromId);
}

std::vector<Edge> AdjacencyMatrix::adjacentNodes(unsigned int nodeId) const {
}

int AdjacencyMatrix::nodeDegree(unsigned int nodeId) const {
    return adjacentNodes(nodeId).size();
}
