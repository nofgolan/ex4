#include "PreProcess.h"
#include "Command1.h"
#include <algorithm>
#include <iostream>

/**
  * Constructor for the Command class
  * @param dio pointer to the DefaultIO object
  * @param CLI_Data pointer to the CLI_Data struct
  * @param description string describing the command
  */
Command1::Command1(DefaultIO *dio, struct CLI_Data *CLI_Data)
        : Command(dio, CLI_Data, "upload an unclassified csv data file") {}

/**
 * This function execute the first command.
 * It reads the path of the local train CSV file and read its data.
 * Then it stores the train file and its names.
 * Then it reads the path of the local test CSV file and read its data.
 * And then it stores the test file data.
 */
void Command1::Execute() {
    dio->write("Please upload your local train CSV file.");
    std::string trainPath;
    trainPath = dio->read();
    dio->write("<<send me " + trainPath);


    //storing train file.
    std::vector<std::vector<double>> train;
    std::vector<std::string> names;

    std::string lineFromClient;

    lineFromClient = dio->read();

    // if line starts with <<, it means en error
    if (lineFromClient.length() >= 2 && lineFromClient[0] == '<' && lineFromClient[1] == '<') {
        dio->write(lineFromClient.substr(2));
        return;
    }

    while (lineFromClient != ">>end") {
        std::vector<std::string> stringVec = split(lineFromClient, ",");
        std::string name = stringVec[stringVec.size() - 1];
        if (std::find(names.begin(), names.end(), name) == names.end()) {
            names.push_back(stringVec.back());
        }
        auto index_of_name = std::find(names.begin(), names.end(), name);
        long index = std::distance(names.begin(), index_of_name);
        stringVec[stringVec.size() - 1] = std::to_string(index);
        // making sure all the numbers are valid.
        if (!inputCheck(stringVec)) {
            dio->write("%%error");
            dio->write("Error: make sure all arguments of csv file are doubles except for names ");
            return;
        }
        // create vector of double.
        std::vector<double> lineValues = convertStringVectortoDoubleVector(stringVec);

        // Add the vector of values to the current line to the main vector
        train.push_back(lineValues);

        // make sure the vector we added is the same length as the first vector in the file.
        if (train[0].size() != lineValues.size()) {
            dio->write("%%error");
            dio->write("Error: not all vectors in file are the same length. ");
            return;
        }
        dio->write("good");
        lineFromClient = dio->read();
    }
    dio->write("Upload complete.");
    cli_Data->train = train;
    cli_Data->names = names;
    dio->write("Please upload your local test CSV file.");

    trainPath = dio->read();
    dio->write("<<send me " + trainPath);
    lineFromClient = dio->read();
    if (lineFromClient.length() >= 2 && lineFromClient[0] == '<' && lineFromClient[1] == '<') {
        dio->write(lineFromClient.substr(2));
        return;
    }
    std::vector<std::vector<double>> test;
    while (lineFromClient != ">>end") {
        std::vector<std::string> stringVec = split(lineFromClient, ",");
        // making sure all the numbers are valid.
        if (!inputCheck(stringVec)) {
            dio->write("%%error");
            dio->write("Error: make sure all arguments of csv file are doubles");
            return;
        }
        // create vector of double.
        std::vector<double> lineValues = convertStringVectortoDoubleVector(stringVec);
        // Add the vector of values to the current line to the main vector
        test.push_back(lineValues);

        // make sure the vector we added is the same length as the first vector in the file.
        if (test[0].size() != lineValues.size()) {
            dio->write("%%error");
            dio->write("Error: not all vectors in file are the same length. ");
            return;
        }
        dio->write("good");
        lineFromClient = dio->read();
    }
    cli_Data->testX = test;
    dio->write("Upload complete.");
}