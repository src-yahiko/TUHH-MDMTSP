#include "mdmtsp.hpp"

void MDMTSP::addDepot(unsigned int depotId)
{
    if (!graph.nodeExists(depotId))
        return;
    depots.insert(depotId);
}

std::vector<unsigned int> MDMTSP::getDepots()
{
    std::vector<unsigned int> depotList;
    for (auto &depotId : depots)
    {
        depotList.push_back(depotId);
    }
    return depotList;
}

bool MDMTSP::isDepot(unsigned int depotId)
{
    return depots.end() != depots.find(depotId);
}

Graph MDMTSP::csf() const
{
    Graph _g = graph;

    unsigned int tempNodeId = __INT_MAX__;
    _g.addNode(tempNodeId);

    for (unsigned int depotId : depots)
        _g.addEdge(tempNodeId, depotId, 0);

    _g.toKruskalMST();

    _g.removeNode(tempNodeId);

    return _g;
}