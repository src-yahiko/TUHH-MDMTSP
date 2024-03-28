#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <random>
#include <vector>
#include <cmath>
#include <algorithm>
#include <sstream>

using std::vector;

struct Node
{
    double x;
    double y;
    int id;
};

struct Edge
{
    Node from;
    Node to;
    double weight;
};

double distance(Node a, Node b);

class Graph
{
    int numNodes = 0;
    vector<Node> nodes;
    vector<Edge> edges;

public:
    Graph() : numNodes(0){};
    Graph(int sizeOfCompleteGraph) : numNodes(0)
    {
        for (int i = 0; i < sizeOfCompleteGraph; ++i)
        {
            addNode(i, i);
        }

        for (int i = 0; i < sizeOfCompleteGraph; ++i)
        {
            for (int j = i + 1; j < sizeOfCompleteGraph; ++j)
            {
                addEdge(nodes[i], nodes[j]);
            }
        }
    }

    double addEdge(Node &from, Node &to);
    void removeEdge(Node &from, Node &to);
    Node &addNode(double x, double y);
    void removeNode(int nodeId);
    // Node& getNodeById(int id);
};
#endif