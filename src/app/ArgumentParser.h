#ifndef ARGUMENTPARSER_H
#define ARGUMENTPARSER_H

#include <string>
#include <vector>
#include <cstdlib>

class ArgumentParser
{

public:
    ArgumentParser(int &argc, char **argv)
    {
        // parseArguments(argc, argv);
    }

    // void parseArguments(int &argc, char **argv);

    static bool checkFlagWithInt(int argc, char **argv, const std::string &flag, int *value)
    {
        for (int i = 1; i < argc - 1; ++i)
        {
            if (std::string(argv[i]) == flag)
            {
                long val = std::strtol(argv[i + 1], nullptr, 10);
                if (val == 0 && argv[i + 1] != std::string("0"))
                    return false;
                *value = static_cast<int>(val);
                return true;
            }
        }
        return false;
    }

    static bool checkFlagWithString(int argc, char **argv, const std::string &flag, std::string *value)
    {
        for (int i = 1; i < argc - 1; ++i)
        {
            if (std::string(argv[i]) == flag)
            {
                *value = argv[i + 1];
                return true; 
            }
        }
        return false;
    }
};

#endif // ARGUMENTPARSER_H
