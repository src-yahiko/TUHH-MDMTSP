#include "graph.hpp"
#include <algorithm>

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

double Graph::edgeWeight(int nodeA, int nodeB) const
{
    auto itNodeA = matrix.find(nodeA);
    if (itNodeA != matrix.end())
    {
        auto itNodeB = itNodeA->second.find(nodeB);
        if (itNodeB != itNodeA->second.end())
            return itNodeB->second;
    }
    return __DBL_MAX__;
}

double Graph::edgeWeight(int nodeA, int nodeB, std::map<int, std::map<int, double>> originalMatrix)
{
    auto itNodeA = originalMatrix.find(nodeA);
    if (itNodeA != originalMatrix.end())
    {
        auto itNodeB = itNodeA->second.find(nodeB);
        if (itNodeB != itNodeA->second.end())
            return itNodeB->second;
    }
    return __DBL_MAX__;
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

Graph Graph::exportRpp(std::map<int, std::map<int, double>> originalMatrix) const
{
    std::set<int> oddNodesSet;
    for (const auto &row : matrix)
    {
        int currentNodeDegree = 0;
        int currentNode = row.first;
        for (const auto &pair : row.second)
        {
            int cmpNode = pair.first;
            if (currentNode != cmpNode)
                currentNodeDegree++;
        }
        if (currentNodeDegree % 2 == 1)
            oddNodesSet.insert(currentNode);
    }

    std::vector<Edge> edges;
    std::vector<int> oddNodes(oddNodesSet.begin(), oddNodesSet.end());
    for (size_t i = 0; i < oddNodes.size(); ++i)
    {
        double minimumWeight = __DBL_MAX__;
        int bestPartner = -1;
        int bestIndex = -1;

        for (size_t j = i + 1; j < oddNodes.size(); ++j)
        {
            double weight = edgeWeight(oddNodes[i], oddNodes[j], originalMatrix);
            std::cout << i << " mit " << j << ": " << weight << " MIN:" << minimumWeight << std::endl;
            if (weight < minimumWeight)
            {
                minimumWeight = weight;
                bestPartner = oddNodes[j];
                bestIndex = j;
            }
        }

        if (bestPartner != -1)
        {
            edges.emplace_back(oddNodes[i], bestPartner, minimumWeight);
            oddNodes.erase(oddNodes.begin() + bestIndex);
        }
    }

    Graph rppGraph = Graph(matrix);
    for (const auto &edge : edges)
        rppGraph.addEdge(edge.from, edge.to, edge.weight);

    return rppGraph;
}