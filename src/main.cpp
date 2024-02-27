#include "app/ArgumentParser.h"
#include "app/MockOutput.h"
#include "graph/CompleteGraph.h"

int main(int argc, char** argv) {
    ArgumentParser parser(argc, argv);

    if (parser.isTest()) 
    {
        std::cout << "Test mode activated." << std::endl;
        // while (true)
        MockOutput::generateOutput();
        return 0;
    }

    int generateMap = -1;
    if (parser.checkFlagWithInt(argc, argv, "-g", &generateMap))
    {
        if (generateMap <= 0 || generateMap > 20)
            return 1;

        auto map = CompleteGraph::getRandomCoordinates(generateMap);
        CompleteGraph::printCoordinates(map);
        return 0;
    }

    // CompleteGraph graph(CompleteGraph::adjacencyMatrixFromCoordinates());

    // graph.printMatrix();

    return 0;
}