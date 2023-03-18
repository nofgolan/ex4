#ifndef ASS4_CLI_H
#define ASS4_CLI_H

#include "DefaultIO.h"
#include "CLI_Data.h"
#include "Command.h"
#include <thread>

class CLI {
    // Member variable to store the DefaultIO object
    DefaultIO *dio;
    // Data object passed to the command objects
    CLI_Data cliData;
    // Array to store command objects
    Command *commands[5];

public:
    // Constructor takes a DefaultIO object as a parameter and stores it as a member variable
    // Also initializes an array of command objects and passes the dio and CLI_Data objects to them
    explicit CLI(DefaultIO *dio);

    // Start the main loop of the command-line interface
    // repeatedly displays a menu of options to the user, waits for the user to enter a choice
    // checks if the choice is valid and if so, executes the corresponding command
    void start();
};


#endif //ASS4_CLI_H
