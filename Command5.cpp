#include "Command5.h"
#include <sstream>
#include <chrono>
#include <thread>

/**
 * Constructor for Command5 class
 * @param dio - pointer to DefaultIO object
 * @param CLI_Data - pointer to CLI_Data struct
 */
Command5::Command5(DefaultIO *dio, struct CLI_Data *CLI_Data) : Command(dio, CLI_Data, "download results") {}

/**
 * Helper function for the Execute method that handles the download process
 * @param dio - pointer to DefaultIO object
 * @param CLI_Data - pointer to CLI_Data struct
 */
void worker(DefaultIO* dio, CLI_Data* CLI_Data) {
    //std::this_thread::sleep_for(std::chrono::milliseconds(100000000 * 5));
    for (size_t i = 0; i < CLI_Data->testY.size(); i++) {
        std::stringstream s;
        s << "@@@ append: " << i + 1 << " " << CLI_Data->names[CLI_Data->testY[i]];
        dio->write(s.str());
    }
    dio->write("@@@ done");
}
/**
 * Overridden Execute method for Command5 class
 * Downloads the results to a file specified by the user
 */
void Command5::Execute() {

    // if there is no data yet write "please upload data"
    if (cli_Data->train.empty() || cli_Data->testX.empty()){
    //if (cli_Data->testY.empty()) {
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

    dio->write("Enter filename to download into");
    std::string filename = dio->read();
    dio->write("<<download " + filename);
    std::thread(worker, this->dio, cli_Data).detach();
}

