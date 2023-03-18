#include "Command4.h"
#include <iostream>
#include <sstream>

/**
 * Constructor for Command4.
 * @param dio pointer to the DefaultIO object being used
 * @param CLI_Data pointer to the CLI_Data struct containing necessary data
 */
Command4::Command4(DefaultIO *dio, struct CLI_Data *CLI_Data) : Command(dio, CLI_Data, "display results") {}
/**
 * Executes the logic for the 'display results' command.
 * Prints the classification results for the test data.
 */
void Command4::Execute() {
    // if there is no data yet write "please upload data"
    if (cli_Data->train.empty() || cli_Data->testX.empty()) {
        // if not all the data was uploaded
        dio->write("please upload data");
        return;
    }
    // if there is no data yet write "please upload data"
    if (cli_Data->testY.empty()) {
        // if not all the data was uploaded
        dio->write("please classify data");
        return;
    }

    //print the Y values
    // loop over the testX lines and get the classification of them.
    for (size_t i = 0; i < cli_Data->testY.size(); i++) {
        std::stringstream s;
        s << i + 1 << " " << cli_Data->names[cli_Data->testY[i]];
        dio->write(s.str());
    }
    dio->write("Done");
}

