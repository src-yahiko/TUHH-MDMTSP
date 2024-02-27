#ifndef MOCKOUTPUT_H
#define MOCKOUTPUT_H

#include <iostream>
#include <unistd.h>

class MockOutput {
public:
    static void generateOutput() {
        std::cout << "MockOutput is generating output..." << std::endl;
        sleep(1);
    }
};

#endif // MOCKOUTPUT_H