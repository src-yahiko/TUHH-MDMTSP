#include "graph.h"

double distance(Node a, Node b)
{
    double dx = b.x - a.x;
    double dy = b.y - a.y;
    return std::sqrt(dx * dx + dy * dy);
};

double Graph::addEdge(Node &from, Node &to)
{
    double dist = distance(from, to);
    Edge newEdge = {from, to, dist};
    edges.emplace_back(newEdge);
    return dist;
};

Node &Graph::addNode(double x, double y)
{
    Node newNode = {x, y, numNodes++};
    nodes.emplace_back(newNode);
    return nodes.back();
};

void Graph::removeNode(int nodeId)
{
    // Remove node from nodes
    auto nodeIt = std::remove_if(nodes.begin(), nodes.end(), [&](const Node &node)
                                 { return node.id == nodeId; });
    nodes.erase(nodeIt, nodes.end());

    // Remove edges to and from node
    auto edgeIt = std::remove_if(edges.begin(), edges.end(), [&](const Edge &edge)
                                 { return edge.from.id == nodeId || edge.to.id == nodeId; });
    edges.erase(edgeIt, edges.end());
};

// Node& Graph::getNodeById(int id) {
//     for (auto& node : nodes)
//         if (node.id == id)
//             return node;

//     throw std::runtime_error("Node with the given ID does not exist.");
// }

// void Graph::removeEdge(Node &from, Node &to)
// {
//     // auto edgeIt = std::remove_if(edges.begin(), edges.end(), [&](const Edge &edge)
//     //                              {
//     //     // Assuming undirected graph
//     //     bool fromFrom = edge.from.x == from.x && edge.from.y == from.y;
//     //     bool fromTo = edge.from.x == to.x && edge.from.y == to.y;
//     //     return fromFrom || fromTo; });
//     // edges.erase(edgeIt, edges.end());
// };
