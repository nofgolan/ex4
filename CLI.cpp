#include "CLI.h"
#include "DefaultIO.h"
#include "CLI_Data.h"
#include "Command1.h"
#include "Command2.h"
#include "Command3.h"
#include "Command4.h"
#include "Command5.h"
#include "sstream"
#include "PreProcess.h"

// Constructor takes a DefaultIO object as a parameter and stores it as a member variable
// Also initializes an array of command objects and passes the dio and CLI_Data objects to them
CLI::CLI(DefaultIO *dio) {
    this->dio = dio;
    commands[0] = new Command1(dio, &cliData);
    commands[1] = new Command2(dio, &cliData);
    commands[2] = new Command3(dio, &cliData);
    commands[3] = new Command4(dio, &cliData);
    commands[4] = new Command5(dio, &cliData);
}

// Start the main loop of the command-line interface
// repeatedly displays a menu of options to the user, waits for the user to enter a choice
// checks if the choice is valid and if so, executes the corresponding command
void CLI::start() {
    while (true) {
        dio->write("Welcome to the KNN classifier Server. Please choose an option:");
        for (int i = 1; i <= 5; i++) {
            std::stringstream ss;
            ss << i << ". " << commands[i - 1]->description;
            dio->write(ss.str());
        }
        dio->write("8. exit");

        std::string userInput;
        userInput = dio->read();
        if (!positiveInteger(userInput)) {
            dio->write("invalid input");
            continue;
        }
        int input = stoi(userInput);


        if (input < 1 || input > 5) {
            dio->write("invalid input");
            continue;
        }
        commands[input - 1]->Execute();
    }
}