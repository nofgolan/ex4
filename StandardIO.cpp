#include <iostream>
#include "StandardIO.h"

using namespace std;

std::string StandardIO::read() {
    // reads a line from standard input and returns it as a string
    std::string line;
    std::getline(std::cin, line);
    return line;
}

void StandardIO::write(std::string line) {
    // writes a line to standard output
    std::cout << line << std::endl;
}
