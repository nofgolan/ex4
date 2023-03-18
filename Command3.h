#ifndef ASS4_COMMAND3_H
#define ASS4_COMMAND3_H

#include "Command.h"
#include "KNN.h"

/**
 * @class Command3
 * @brief Class for handling the "classify data" command
 *
 * This class inherits from the Command class and overrides the Execute function to handle the "classify data" command.
 * It uses the KNN class to classify the test data using the train data and the specified K and distance metric.
 */

class Command3 :public Command{

public:
    /**
     * @brief Constructor for Command3
     *
     * @param dio pointer to DefaultIO object for input/output operations
     * @param CLI_Data pointer to struct containing all data for the command line interface
     */
    Command3();

    Command3(DefaultIO *dio, struct CLI_Data *CLI_Data);
    /**
     * @brief Overridden Execute function to handle the "classify data" command
     *
     * This function checks if data has been uploaded, and if not, prompts the user to upload data.
     * Then it uses the KNN class to classify the test data using the train data and the specified K and distance metric.
     */
    void Execute();


};


#endif //ASS4_COMMAND3_H
