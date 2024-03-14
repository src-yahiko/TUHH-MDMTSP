#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <random>
#include <vector>
#include <cmath>
#include <algorithm>
#include <sstream>

using namespace std;

struct Node
{
    int index;
    vector<double> position;
};

struct Edge
{
    int from;
    int to;
    double weight;
    string color;
};

class CompleteGraph
{
    struct TreeNode
    {
        int parent;
        int rank;
    };

    vector<TreeNode> treeNodes;
    vector<Node> nodes;
    vector<Edge> edges;

    double static random_number()
    {
        static random_device rd;
        static mt19937 gen(rd());
        static uniform_real_distribution<> dis(0.0, 1.0);
        return dis(gen);
    }

    double static distance(const Node &x, const Node &y)
    {
        double dx = x.position[0] - y.position[0];
        double dy = x.position[1] - y.position[1];
        return sqrt(dx * dx + dy * dy);
    }

public:
    CompleteGraph(vector<Node> inputNodes) : nodes(inputNodes)
    {
        int numberOfNodes = inputNodes.size();

        treeNodes.resize(numberOfNodes);
        for (int i = 0; i < numberOfNodes; i++)
            treeNodes[i] = {i, 0};

        for (int i = 0; i < numberOfNodes - 1; i++)
        {
            for (int j = i + 1; j < numberOfNodes; j++)
                edges.push_back({i, j, distance(nodes[i], nodes[j]), "FF5733"});
        }
    }

    CompleteGraph(int numberOfNodes) : treeNodes(numberOfNodes)
    {
        for (int i = 0; i < numberOfNodes; i++)
        {
            nodes.push_back({i, {random_number(), random_number()}});
            treeNodes[i] = {i, 0};
        }

        for (int i = 0; i < numberOfNodes - 1; i++)
        {
            for (int j = i + 1; j < numberOfNodes; j++)
                edges.push_back({i, j, distance(nodes[i], nodes[j]), "FF5733"});
        }
    }

    int treeFind(int index)
    {
        if (treeNodes[index].parent != index)
        {
            treeNodes[index].parent = treeFind(treeNodes[index].parent);
        }
        return treeNodes[index].parent;
    }

    void treeUnion(int x, int y)
    {
        int rootX = treeFind(x);
        int rootY = treeFind(y);

        if (treeNodes[rootX].rank < treeNodes[rootY].rank)
        {
            treeNodes[rootX].parent = rootY;
        }
        else if (treeNodes[rootX].rank > treeNodes[rootY].rank)
        {
            treeNodes[rootY].parent = rootX;
        }
        else
        {
            treeNodes[rootY].parent = rootX;
            treeNodes[rootX].rank++;
        }
    }

    vector<Edge> MstKruskal()
    {
        std::sort(edges.begin(), edges.end(), [](const Edge &a, const Edge &b)
                  { return a.weight < b.weight; });

        vector<Edge> mst;
        mst.reserve(nodes.size() - 1);

        for (auto &edge : edges)
        {
            int root1 = treeFind(edge.from);
            int root2 = treeFind(edge.to);

            if (root1 != root2)
            {
                treeUnion(root1, root2);
                mst.push_back(edge);

                if (mst.size() == nodes.size() - 1)
                    break;
            }
        }

        return mst;
    }

    static vector<Node> parsePositions(const std::string &input)
    {
        vector<Node> nodes;
        istringstream stream(input);
        string token;
        vector<string> tokens;
        while (std::getline(stream, token, '_'))
        {
            tokens.push_back(token);
        }

        size_t numNodes;
        istringstream(tokens[0]) >> numNodes;

        if (tokens.size() != 1 + (numNodes * 2))
        {
            cerr << "Invalid input format." << endl;
            return nodes;
        }

        double x, y;
        for (size_t i = 1; i < tokens.size(); i += 2)
        {
            istringstream(tokens[i]) >> x;
            istringstream(tokens[i + 1]) >> y;
            nodes.push_back((Node){(int)(i - 1), {x, y}});
        }

        return nodes;
    }

    void printNodes()
    {
        cout << "#MAP#" << nodes.size();
        for (const Node &node : nodes)
            cout << "_" << node.position[0] << "_" << node.position[1];
    }

    static void printMst(const vector<Edge> &edges)
    {
        cout << "#MST#" << edges.size();
        for (const Edge &edge : edges)
            cout << "_" << edge.from << "_" << edge.to << "_" << edge.color;
    }
};

#endif // GRAPH_H