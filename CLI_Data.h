#ifndef ASS4_CLI_DATA_H
#define ASS4_CLI_DATA_H

#include <string>
#include <vector>
/**
* CLI_Data is a struct that contains all the data required for running a command line interface
*
* @field k: an integer representing the number of nearest neighbors to be used in the algorithm
* @field disType: a string representing the distance type to be used in the algorithm (e.g. "euclidean")
* @field train: a 2D vector of doubles representing the training data
* @field testX: a 2D vector of doubles representing the test data (inputs)
* @field testY: a vector of doubles representing the test data (outputs)
* @field names: a vector of strings representing the names of the data points
*/
struct CLI_Data {
    int k;
    std::string disType;
    std::vector<std::vector<double>> train;
    std::vector<std::vector<double>> testX;
    std::vector<double> testY;
    std::vector<std::string> names;

    CLI_Data();
};


#endif //ASS4_CLI_DATA_H
