#ifndef ASS4_DEFAULTIO_H
#define ASS4_DEFAULTIO_H

#include <string>

/**
 * DefaultIO is an abstract class that defines the interface for reading and writing input/output.
 * It is intended to be subclassed by concrete classes that implement the read and write methods
 * in a specific way.
 */
class DefaultIO {
public:
    /**
 * Read a line of input.
 * @return a string containing the line of input.
 */
    virtual std::string read() = 0;
    /**
     * Write a line of output.
     * @param line the line of output to be written.
     */
    virtual void write(std::string line) = 0;

};


#endif //ASS4_DEFAULTIO_H
