#include "graph/graph.cpp"
#include "application.hpp"
#include <stdlib.h>
#include <cstring>

int main(int argc, char *argv[])
{
    Main m;
    if (argc == 1)
    {
        m.randomGraph();
    }
    else if (argc == 2)
    {
        m.randomGraph((int)strtol(argv[1], NULL, 10));
    }
    else if (argc == 3)
    {
        if (std::strcmp(argv[1], "MST") == 0)
        {
            Application app = m.getApplication(argv[2]);
            printReset();
            printPoints(app.cities);
            printDepots(app.getDepots());
            printEdges(app.g.exportMst().getEdges());
        }
        else if (std::strcmp(argv[1], "CSF") == 0)
        {
            Application app = m.getApplication(argv[2]);
            printReset();
            printPoints(app.cities);
            printDepots(app.getDepots());
            auto csfEdges = app.g.exportCsf(app.getDepots()).getEdges();
            printEdges(csfEdges);
            double w = 0;
            for (auto &edge : csfEdges)
                w += edge.weight;
            double eps = 0.1;
            std::cout << "Epsilon: " << eps << std::endl;
            std::cout << "CSF weight: " << w << std::endl;
            std::cout << "Depot count: " << app.getDepots().size() << std::endl;
            double b = (eps / app.getDepots().size()) * w;
            std::cout << "Heavy eps boundary: " << b << std::endl;
            for (auto &edge : csfEdges)
            {
                if (edge.weight > b)
                    std::cout << "Edge: " << edge.from << ", " << edge.to << ", " << edge.weight << std::endl;
            }
        }
        else if (std::strcmp(argv[1], "DRPP") == 0)
        {
            Application app = m.getApplication(argv[2]);
            printReset();
            printPoints(app.cities);
            printDepots(app.getDepots());
            printEdges(app.g.exportCsf(app.getDepots()).exportRpp(app.g.matrix).getEdges());
        }
    }
    return 0;
}