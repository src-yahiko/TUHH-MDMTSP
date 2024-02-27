#include "app/ArgumentParser.h"
#include "app/MockOutput.h"

int main(int argc, char** argv) {
    ArgumentParser parser(argc, argv);
    MockOutput output;

    if (parser.isTest()) 
    {
        std::cout << "Test mode activated." << std::endl;
        while (true)
            output.generateOutput();
        
        return 0;
    }

    return 0;
}
