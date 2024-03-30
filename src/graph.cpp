#include "graph.hpp"
#include <algorithm>

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
