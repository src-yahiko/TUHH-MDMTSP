#include "graph.cpp"

#include <iostream>
#include <random>

struct Point
{
    double x, y;
};

static double randomNumber()
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(0.0, 1.0);
    return dis(gen);
};

static double distance(double ax, double ay, double bx, double by)
{
    double dx = bx - ax;
    double dy = by - ay;
    return std::sqrt(dx * dx + dy * dy);
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

int main()
{
    int numCities = 20;
    std::vector<Point> cities;
    std::vector<int> depots;

    for (int i = 0; i < numCities; ++i)
        cities.emplace_back(Point{randomNumber(), randomNumber()});

    Graph g = Graph();

    for (int i = 0; i < numCities; ++i)
    {
        if (randomNumber() > .85)
            depots.push_back(i);

        for (int j = i + 1; j < numCities; ++j)
            g.addEdge(i, j, distance(cities[i].x, cities[i].y, cities[j].x, cities[j].y));
    }

    std::cout << "#RESET#" << std::endl;
    printPoints(cities);
    printDepots(depots);
    printEdges(g.exportCsf(depots).getEdges());
    return 0;
}