#ifndef APPLICATION_HPP
#define APPLICATION_HPP
#define MODE_GUI 0
#define MODE_BENCHMARK 1

#include "graph/graph.hpp"

#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <fstream>

class Application
{
    std::set<int> depots;

public:
    Graph g;

    std::map<int, Point> cities;
    static void trim(std::string &s)
    {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch)
                                        { return !std::isspace(ch); }));
        s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch)
                             { return !std::isspace(ch); })
                    .base(),
                s.end());
    }
    void parseLine(std::string line)
    {
        trim(line);

        if (line.empty() || line[0] != '#')
            return;
        std::replace(line.begin(), line.end(), '#', ' ');
        std::replace(line.begin(), line.end(), '_', ' ');

        std::istringstream iss(line);
        std::string type;
        iss >> type;

        if (type == "POINT")
        {
            int id;
            double x, y;
            iss >> id >> x >> y;
            cities[id] = Point{x, y};
        }
        else if (type == "DEPOT")
        {
            int id;
            iss >> id;
            depots.insert(id);
        }
    }

    void parseFile(std::string filename, int mode)
    {
        std::ifstream file(filename);
        if (!file.is_open())
        {
            std::cerr << "Failed to open file: " << filename << std::endl;
            return;
        }

        if (mode == MODE_GUI)
        {
            std::string line;
            while (getline(file, line))
                parseLine(line);
        }
        else if (mode == MODE_BENCHMARK)
        {
        }

        file.close();
    }
    void parseParam(std::string param)
    {
        trim(param);
        std::replace(param.begin(), param.end(), '\n', ' ');

        std::istringstream iss(param);
        std::string line;
        while (iss >> line)
            parseLine(line);
    }
    std::vector<int> getDepots()
    {
        return std::vector<int>(depots.begin(), depots.end());
    }
    Graph getCompleteGraph()
    {
        Graph g;
        for (auto it1 = cities.begin(); it1 != cities.end(); ++it1)
        {
            auto it2 = it1;
            ++it2; // Startet bei dem Element nach it1, um Duplikate zu vermeiden und keine Kante zweimal zu zählen
            for (; it2 != cities.end(); ++it2)
            {
                double weight = std::sqrt(std::pow(it1->second.x - it2->second.x, 2) +
                                          std::pow(it1->second.y - it2->second.y, 2));
                g.addEdge(it1->first, it2->first, weight);
                g.addEdge(it2->first, it1->first, weight); // Falls der Graph ungerichtet ist
            }
        }
        return g;
    }
};

class Main
{
public:
    void randomGraph()
    {
        int numCities = 7;
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
        printEdges(g.getEdges());
    }

    void randomGraph(int n)
    {
        int numCities = n;
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
        printEdges(g.getEdges());
    }

    void inputGraph(std::string fp, int r)
    {
        Application app;
        app.parseFile(fp, MODE_GUI);
        Graph g = app.getCompleteGraph();

        printReset();
        printPoints(app.cities);
        printDepots(app.getDepots());
    }

    Application getApplication(std::string param)
    {
        Application app;
        app.parseParam(param);
        app.g = app.getCompleteGraph();
        return app;
    }
};

#endif
