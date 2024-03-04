#include "app/ArgumentParser.h"
#include "app/MockOutput.h"
#include "graph/CompleteGraph.h"
#include <string.h>

int main(int argc, char **argv)
{
    ArgumentParser parser(argc, argv);

    if (parser.isTest())
    {
        std::cout << "Test mode activated." << std::endl;
        MockOutput::generateOutput();
        return 0;
    }

    int generateMap = -1;
    if (parser.checkFlagWithInt(argc, argv, "-m", &generateMap))
    {
        if (generateMap <= 0 || generateMap > 20)
            return 1;

        auto map = CompleteGraph::getRandomCoordinates(generateMap);
        CompleteGraph::printCoordinates(map);
        return 0;
    }

    std::string inputCoordinates = "";
    if (parser.checkFlagWithString(argc, argv, "-g", &inputCoordinates))
    {
        auto coordinates = CompleteGraph::parseCoordinates(inputCoordinates);
        auto matrix = CompleteGraph::adjacencyMatrixFromCoordinates(coordinates);
        CompleteGraph graph(matrix);
        graph.printMatrix();
        return 0;
    }

    return 0;
}