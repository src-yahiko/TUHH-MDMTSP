#include "graph.cpp"
#include "mdmtsp.cpp"

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
        points.emplace_back(Point{randomNumber(), randomNumber()});

    return points;
}

void printEdges(std::vector<Edge> edges)
{
    std::cout << "EDGES" << std::endl;
    std::cout << edges.size() << std::endl;
    for (const auto &edge : edges)
        std::cout << edge.from << " " << edge.to << " " << edge.weight << std::endl;
}

void printDepots(std::vector<unsigned int> nodes)
{
    std::cout << "DEPOTS" << std::endl;
    std::cout << nodes.size() << std::endl;
    for (const auto &node : nodes)
        std::cout << node << std::endl;
}

void printPoints(std::vector<Point> points)
{
    std::cout << "POINTS" << std::endl;
    std::cout << points.size() << std::endl;
    for (std::vector<Point>::size_type i = 0; i < points.size(); ++i)
        std::cout << i << " " << points[i].x << " " << points[i].y << std::endl;
}

int main()
{
    std::vector<Point> cities = randomPoints(20);
    std::vector<unsigned int> depots;

    Graph g = Graph();

    for (unsigned int i = 0; i < cities.size(); ++i)
    {
        g.addNode(i);
        if (randomNumber() > .8)
            depots.push_back(i);
    }

    for (unsigned int i = 0; i < cities.size(); ++i)
        for (unsigned int j = i + 1; j < cities.size(); ++j)
            g.addEdge(i, j, distance(cities[i].x, cities[i].y, cities[j].x, cities[j].y));

    MDMTSP mdmtsp = MDMTSP(g);
    for (unsigned int depotId : depots)
        mdmtsp.addDepot(depotId);

    Graph _g_csf = mdmtsp.csf();
    // for (Edge &edge : _g_csf.getEdges())
    //     std::cout << edge.from << " - " << edge.to << " : " << edge.weight << std::endl;

    printPoints(cities);
    printEdges(_g_csf.getEdges());
    printDepots(mdmtsp.getDepots());
    return 0;
};