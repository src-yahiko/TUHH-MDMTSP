#include "graph.h"

static double randomNumber()
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(0.0, 1.0);
    return dis(gen);
};

// static double distance(Node a, Node b)
// {
//     double dx = b.x - a.x;
//     double dy = b.y - a.y;
//     return std::sqrt(dx * dx + dy * dy);
// };