#include "graph.hpp"
#include <algorithm>
#define NODE_NOT_FOUND __INT_MAX__

double Graph::tourCost(const std::vector<Edge> tour)
{
    double weight = 0;
    for (const auto &edge : tour)
        weight += edge.weight;
    return weight;
}

void Graph::addEdge(int fromId, int toId, double weight)
{
    matrix[fromId][toId] = weight;
    matrix[toId][fromId] = weight;
}

void Graph::removeNode(int targetId)
{
    matrix.erase(targetId);
    for (auto &row : matrix)
        row.second.erase(targetId);
}

void Graph::removeEdge(int fromId, int toId)
{
    matrix[fromId].erase(toId);
    matrix[toId].erase(fromId);
}

std::vector<Edge> Graph::getEdges() const
{
    std::vector<Edge> edges;
    for (const auto &row : matrix)
    {
        int fromId = row.first;
        for (const auto &elem : row.second)
        {
            int toId = elem.first;
            double weight = elem.second;
            if (fromId > toId || weight == -1)
                continue;
            edges.emplace_back(fromId, toId, weight);
        }
    }
    return edges;
}

Graph Graph::exportMst() const
{
    Graph mstGraph = Graph();

    std::vector<Edge> edges = getEdges();
    std::sort(edges.begin(), edges.end());

    UnionFind uf;
    for (const auto &pair : matrix)
    {
        int nodeId = pair.first;
        uf.parent[nodeId] = nodeId;
        uf.rank[nodeId] = 0;
    }

    for (const auto &edge : edges)
    {
        if (uf.find(edge.from) != uf.find(edge.to))
        {
            uf.unite(edge.from, edge.to);
            mstGraph.addEdge(edge.from, edge.to, edge.weight);
        }
    }

    return mstGraph;
}

Graph Graph::exportCsf(const std::vector<int> depots) const
{
    Graph csfGraph = Graph(matrix);
    int tempNode = -1;
    for (const auto &depotId : depots)
        csfGraph.addEdge(tempNode, depotId, 0);

    csfGraph = csfGraph.exportMst();
    csfGraph.removeNode(tempNode);
    return csfGraph;
}

int UnionFind::find(int nodeId)
{
    if (parent.find(nodeId) == parent.end())
        return NODE_NOT_FOUND;

    if (parent[nodeId] != nodeId)
        parent[nodeId] = find(parent[nodeId]);

    return parent[nodeId];
}

void UnionFind::unite(int nodeA, int nodeB)
{
    int rootA = find(nodeA);
    int rootB = find(nodeB);

    if (rootA == NODE_NOT_FOUND || rootB == NODE_NOT_FOUND)
        return;

    if (rootA == rootB)
        return;

    if (rank[rootA] < rank[rootB])
    {
        parent[rootA] = rootB;
    }
    else if (rank[rootA] > rank[rootB])
    {
        parent[rootB] = rootA;
    }
    else
    {
        parent[rootB] = rootA;
        rank[rootA]++;
    }
}