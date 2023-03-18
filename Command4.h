
#ifndef ASS4_COMMAND4_H
#define ASS4_COMMAND4_H

#include "Command.h"


class Command4 : public Command {

public:
    /**
    * Constructor for Command4 class.
    *
    * @param dio pointer to DefaultIO object for input/output operations
    * @param CLI_Data pointer to struct containing the data for the command line interface
    */
    Command4(DefaultIO *dio, struct CLI_Data *CLI_Data);
    /**
      * Executes the command for displaying the results of the classification.
      *
      * This method first checks if the testY data is empty. If it is, it prints "please upload data" and returns.
      * Otherwise, it loops through the testY data and prints each result along with its corresponding index.
      * Then it prints "Done".
      */
    void Execute() override;

};

#endif //ASS4_COMMAND4_H