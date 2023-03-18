#ifndef ASS4_COMMAND5_H
#define ASS4_COMMAND5_H

#include "Command.h"
#include "DefaultIO.h"

class Command5 : public Command {

public:
    /**
    * Constructor that creates an instance of Command5.
    * @param dio Pointer to the DefaultIO object used for input/output.
    * @param CLI_Data Pointer to the struct CLI_Data object that holds the data used in the command.
    */
    Command5(DefaultIO *dio, struct CLI_Data *CLI_Data);
    /**
    * Executes the command. This function is responsible for downloading the results of the classification.
    */
    void Execute() override;

};

#endif //ASS4_COMMAND5_H
