#include "graph/graph.cpp"

int main()
{
    int numCities = 20;
    std::vector<Point> cities = generatePoints(numCities);
    std::vector<int> depots;

    Graph g = Graph();

    for (int i = 0; i < numCities; ++i)
    {
        if (randomNumber() > .85)
            depots.push_back(i);

        for (int j = i + 1; j < numCities; ++j)
            g.addEdge(i, j, distance(cities[i], cities[j]));
    }

    printReset();
    printPoints(cities);
    printDepots(depots);
    printEdges(g.exportCsf(depots).getEdges());
    return 0;
}