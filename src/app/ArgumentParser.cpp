#include "ArgumentParser.h"

void ArgumentParser::parseArguments(int& argc, char** argv) {
    for (int i = 1; i < argc; ++i) { 
        std::string arg = argv[i];
        if (arg == "--test") {
            testing = true;
        }
    }
}
