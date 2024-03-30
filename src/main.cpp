#include "graph.hpp"

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

static std::vector<Point> randomPoints(unsigned int size)
{
    std::vector<Point> points;

    for (unsigned int i = 0; i < size; ++i)
        points[i] = Point{randomNumber(), randomNumber()};
    
    return points;
}

int main()
{
    Graph g = Graph();

    std::vector<Point> cities = randomPoints(20);
    for (unsigned int i = 0; i < cities.size(); ++i)
        g.addNode(i);

    for (unsigned int i = 0; i < cities.size(); ++i)
        for (unsigned int j = i + 1; i < cities.size(); ++j)
            g.addEdge(i, j, distance(cities[i].x, cities[i].y, cities[j].x, cities[j].y));

    return 0;
};