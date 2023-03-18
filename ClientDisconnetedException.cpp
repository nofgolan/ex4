
#include "ClientDisconnetedException.h"
/**
* @brief Custom exception for when a client disconnects from the server.
* @param message - the message to be passed to the exception object
*/
ClientDisconnetedException::ClientDisconnetedException(const std::string message) {
    this->message = message;
}
/**
* @brief Returns the message passed to the exception object.
* @return the message passed to the exception object
*/
const char* ClientDisconnetedException::what() const throw() {
    return this->message.c_str();
}