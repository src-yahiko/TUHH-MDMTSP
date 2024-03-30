#include "graph.hpp"
#include <algorithm>
#include <iostream>

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

Graph::Graph(){};

bool Graph::nodeExists(unsigned int nodeId) const
{
    auto it = nodes.find(nodeId);
    if (it != nodes.end())
        return true;
    return false;
}

void Graph::addNode(unsigned int nodeId)
{
    nodes.insert(nodeId);
}

void Graph::removeNode(unsigned int nodeId)
{
    nodes.erase(nodeId);
}

void Graph::addNodes(const std::vector<unsigned int> nodeList)
{
    for (const auto &node : nodeList)
        addNode(node);
}

void Graph::removeNodes(const std::vector<unsigned int> nodeList)
{
    for (const auto &node : nodeList)
        removeNode(node);
}

void Graph::addEdge(unsigned int fromId, unsigned int toId, double weight)
{
    if (!nodeExists(fromId))
        addNode(fromId);

    if (!nodeExists(toId))
        addNode(toId);

    edges.emplace_back(fromId, toId, weight);
    matrix.addEdge(fromId, toId, weight);
}

void Graph::removeEdge(unsigned int fromId, unsigned int toId, double weight)
{
    Edge cmp = Edge(fromId, toId, weight);

    edges.erase(std::remove_if(edges.begin(), edges.end(), [&](Edge edge)
                               { return cmp.from == edge.from && cmp.to == edge.to && cmp.weight == edge.weight; }));
    matrix.removeEdge(fromId, toId);
}

void Graph::addEdges(std::vector<Edge> edgeList)
{
    for (const auto &edge : edgeList)
        addEdge(edge.from, edge.to, edge.weight);
}

void Graph::removeEdges(std::vector<Edge> edgeList)
{
    for (const auto &edge : edgeList)
        removeEdge(edge.from, edge.to, edge.weight);
}

std::vector<unsigned int> Graph::getNodes() const
{
    std::vector<unsigned int> nodeIDs;

    for (const auto &nodeId : nodes)
        nodeIDs.push_back(nodeId);

    return nodeIDs;
}

std::vector<Edge> Graph::getEdges() const
{
    return edges;
}