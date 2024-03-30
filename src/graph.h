#ifndef GRAPH_H
#define GRAPH_H

#include "types.h"
#include <random>

static double randomNumber();

static double distance(double, double, double, double);

class Graph {
    std::map<unsigned int, Node> matrix;
    std::vector<Edge> edges;
};

#endif