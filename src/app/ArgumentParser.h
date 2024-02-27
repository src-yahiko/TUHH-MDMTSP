#ifndef ARGUMENTPARSER_H
#define ARGUMENTPARSER_H

#include <string>
#include <vector>

class ArgumentParser {
private:
    bool testing = false;

public:
    ArgumentParser(int& argc, char** argv) {
        parseArguments(argc, argv);
    }

    void parseArguments(int& argc, char** argv);

    bool isTest() const {
        return testing;
    }
};

#endif // ARGUMENTPARSER_H
