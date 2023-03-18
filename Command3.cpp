#include "Command3.h"
#include "PreProcess.h"
#include "KNN.h"


Command3::Command3(DefaultIO *dio, struct CLI_Data *CLI_Data) : Command(dio, CLI_Data, "classify data") {}

/**
 * @brief Execute the command
 *
 * This method attempts to classify the test data using the KNN algorithm.
 * It checks if the training data has been uploaded, if not it returns a message to upload data.
 * The method creates an instance of the KNN class and uses the classify method to classify the test data.
 * The classified data is stored in the CLI_Data struct.
 */
void Command3::Execute() {
    // if there is no data yet write "please upload data"
    if (cli_Data->train.empty() || cli_Data->testX.empty()) {
        // if not all the data was uploaded
        dio->write("please upload data");
        return;
    }


    // loop over the testX lines and get the classification of them.
    KNN *knn = new KNN(cli_Data->train);
    cli_Data->testY = std::vector<double>();
    for (size_t i = 0; i < cli_Data->testX.size(); i++) {
        cli_Data->testY.push_back(knn->classify(cli_Data->testX[i], cli_Data->k, cli_Data->disType, cli_Data->names.size()));
    }
    delete knn;
    dio->write("classifying data complete");
}
