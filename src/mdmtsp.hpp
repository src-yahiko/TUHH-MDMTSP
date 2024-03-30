#ifndef MDMTSP_HPP
#define MDMTSP_HPP

#include "graph.hpp"
class MDMTSP
{
    Graph graph;
    std::set<unsigned int> depots;

public:
    MDMTSP(Graph g) : graph(g){};
    void addDepot(unsigned int);
    std::vector<unsigned int> getDepots();
    bool isDepot(unsigned int);
    Graph csf() const;
};

#endif