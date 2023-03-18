#include "Command.h"

Command::Command(DefaultIO *dio, struct CLI_Data *CLI_Data, std::string description) {
    /**
 *
 * @param dio pointer to a DefaultIO object that will be used for input/output operations
 * @param CLI_Data pointer to a struct containing data for the command line interface
 * @param description a string describing the purpose of the command
 */
    this->dio = dio;
    this->cli_Data = CLI_Data;
    this->description = description;
}
