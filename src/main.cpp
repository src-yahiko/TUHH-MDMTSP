#include "app/ArgumentParser.h"
#include "graph/Graph.h"

using namespace std;

int main(int argc, char **argv)
{
    ArgumentParser parser(argc, argv);

    int numberOfNodes = -1;
    if (parser.checkFlagWithInt(argc, argv, "-c", &numberOfNodes))
    {
        if (numberOfNodes <= 0 || numberOfNodes > 30)
            return 1;

        CompleteGraph graph = CompleteGraph(numberOfNodes);
        graph.printNodes();
        return 0;
    }

    string inputNodes = "";
    if (parser.checkFlagWithString(argc, argv, "-i", &inputNodes))
    {
        vector<Node> nodes = CompleteGraph::parsePositions(inputNodes);
        CompleteGraph graph = CompleteGraph(nodes);
        vector<Edge> mst = graph.MstKruskal();
        graph.printMst(mst);
        return 0;
    }

    return 0;
}