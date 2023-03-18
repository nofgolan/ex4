#include "Command2.h"
#include "PreProcess.h"
#include <sstream>
#include <vector>
#include "PreProcess.h"
/**
* Class representing the command to set the algorithm settings
*/
/**
* Constructor for Command2
* @param dio DefaultIO object to handle input/output
* @param CLI_Data struct containing the current algorithm settings
*/
Command2::Command2(DefaultIO *dio, struct CLI_Data *CLI_Data)
        : Command(dio, CLI_Data, "algorithm settings") {}
/**
* Function to execute the command, sets the algorithm settings based on user input
*/
void Command2::Execute() {
    std::stringstream ss;
    ss << "The current KNN parameters are: K = " << cli_Data->k << ", distance metric = " << cli_Data->disType;
    dio->write(ss.str());
    std::string read = dio->read();

    if (read.empty()) {
        return;
    }
    std::vector<std::string> vs1 = split(read, " ");
    if (vs1.size() != 2) {
        dio->write("There should be 2 variables, K and distance metric");
        return;
    }
    if (!positiveInteger(vs1[0]) && !distanceMetric(vs1[1])) {
        dio->write("invalid input for K and invalid input for metric");
        return;
    }
    if (!positiveInteger(vs1[0])) {
        dio->write("invalid input for K");
        return;
    }
    if (!distanceMetric(vs1[1])) {
        dio->write("invalid input for metric");
        return;
    }
    cli_Data->k = stoi(vs1[0]);
    cli_Data->disType = vs1[1];
}

