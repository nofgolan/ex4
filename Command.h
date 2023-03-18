#ifndef ASS4_COMMAND_H
#define ASS4_COMMAND_H

#include <string>
#include "DefaultIO.h"
#include "CLI_Data.h"

class Command {
protected:
    DefaultIO *dio;
    CLI_Data *cli_Data;
public:
    /**
* The description of the command
*/
    std::string description;
    /**
* Constructor for the Command class.
* @param dio A pointer to the default input/output object
* @param CLI_Data A pointer to the CLI_Data struct
* @param description The description of the command
*/

    Command(DefaultIO *dio, struct CLI_Data *CLI_Data, std::string description);
    /**
    * Virtual destructor for the Command class
    */
    virtual ~Command() = default;
    /**
    * Virtual function that will be overriden by the derived classes to execute the command
    */
    virtual void Execute() = 0;


};


#endif //ASS4_COMMAND_H
