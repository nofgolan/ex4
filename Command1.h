#ifndef ASS4_COMMAND1_H
#define ASS4_COMMAND1_H

#include "Command.h"
#include <string>
#include "DefaultIO.h"
#include "CLI_Data.h"

class Command1 : public Command {
public:
    /**
 * @brief Constructor for the Command1 class
 *
 * @param dio pointer to an instance of the DefaultIO class
 * @param CLI_Data pointer to an instance of the CLI_Data struct
 *
 * This constructor takes in two pointers as input, one to an instance of the DefaultIO class and another to an instance of the CLI_Data struct.
 * The DefaultIO pointer is used for input/output operations and the CLI_Data pointer is used to store the train, test and names data.
 */
    Command1(DefaultIO *dio, struct CLI_Data *CLI_Data);
    /**
     * @brief Executes the command for uploading a CSV file
     *
     * This function is used to upload a CSV file, it reads the file from the user and stores it in the CLI_Data struct as train and test data.
     * The function also checks for errors in the file and sends an error message if there is any.
     *
     */
    void Execute() override;
};

#endif //ASS4_COMMAND1_H
