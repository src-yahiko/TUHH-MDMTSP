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
            printEdges(app.g.exportCsf(app.getDepots()).getEdges());
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