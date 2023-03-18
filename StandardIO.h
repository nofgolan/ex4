
#ifndef ASS4_STANDARDIO_H
#define ASS4_STANDARDIO_H

#include "DefaultIO.h"
#include <string>

// This class implements the DefaultIO interface for standard input and output
class StandardIO : public DefaultIO {
public:
    // reads a line from standard input and returns it as a string
    std::string read() override;
// writes a line to standard output
    void write(std::string line) override;
};


#endif //ASS4_STANDARDIO_H
