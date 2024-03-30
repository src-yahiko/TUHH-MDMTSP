#include "graph.h"

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