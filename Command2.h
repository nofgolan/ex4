#ifndef ASS4_COMMAND2_H
#define ASS4_COMMAND2_H

#include "Command.h"
#include <string>
#include "DefaultIO.h"
#include "CLI_Data.h"

class Command2 : public Command {
public:
    /**
    * Constructor for Command2
    * @param dio - pointer to DefaultIO object for input/output operations
    * @param CLI_Data - pointer to struct containing CLI data
    */
    Command2(DefaultIO *dio, struct CLI_Data *CLI_Data);
    /**
     * Executes the command
     * Prints out the current KNN parameters, then reads input and updates the parameters if the input is valid
     */
    void Execute() override;

};


#endif //ASS4_COMMAND2_H
