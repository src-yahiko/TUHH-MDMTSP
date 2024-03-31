#ifndef UTILS_HPP
#define UTILS_HPP

#define NODE_NOT_FOUND __INT_MAX__

#include <map>
#include <set>
#include <vector>
#include <random>
#include <iostream>

struct Edge
{
    int from, to;
    double weight;

    Edge(int f, int t, double w) : from(std::min(f, t)), to(std::max(f, t)), weight(w) {}

    bool operator<(const Edge &other) const
    {
        if (weight == other.weight)
        {
            if (from == other.from)
                return to < other.to;
            return from < other.from;
        }
        return weight < other.weight;
    }
};

struct Point
{
    double x, y;
};

double distance(Point a, Point b)
{
    double dx = b.x - a.x;
    double dy = b.y - a.y;
    return std::sqrt(dx * dx + dy * dy);
};

static double randomNumber()
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(0.0, 1.0);
    return dis(gen);
};

std::vector<Point> generatePoints(int numCities)
{
    std::vector<Point> cities;
    for (int i = 0; i < numCities; ++i)
        cities.emplace_back(Point{randomNumber(), randomNumber()});
    return cities;
}

class UnionFind
{
public:
    std::map<int, int> parent;
    std::map<int, int> rank;

    int find(int nodeId)
    {
        if (parent.find(nodeId) == parent.end())
            return NODE_NOT_FOUND;

        if (parent[nodeId] != nodeId)
            parent[nodeId] = find(parent[nodeId]);

        return parent[nodeId];
    }

    void unite(int nodeA, int nodeB)
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
};

void printPoints(std::vector<Point> points)
{
    for (std::vector<Point>::size_type i = 0; i < points.size(); ++i)
        std::cout << "#POINT#" << i << "_" << points[i].x << "_" << points[i].y << std::endl;
}

void printDepots(std::vector<int> nodes)
{
    for (const auto &node : nodes)
        std::cout << "#DEPOT#" << node << std::endl;
}

void printEdges(std::vector<Edge> edges)
{
    for (const auto &edge : edges)
        std::cout << "#EDGE#" << edge.from << "_" << edge.to << "_" << edge.weight << std::endl;
}

void printReset()
{
    std::cout << "#RESET#" << std::endl;
}

#endif
