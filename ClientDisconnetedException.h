//
// Created by Nof Golan on 24/01/2023.
//

#ifndef EX4_FINAL_CLIENTDISCONNETEDEXCEPTION_H
#define EX4_FINAL_CLIENTDISCONNETEDEXCEPTION_H

#include <exception>
#include <string>

class ClientDisconnetedException : public std::exception
{
private:
    std::string message;
public:
    /**
     * Constructor for the ClientDisconnetedException class, which initializes the exception message.
     * @param message The message to be stored in the exception.
     */
    ClientDisconnetedException(const std::string message);
    /**
     * Returns the message stored in the exception.
     * @return The message stored in the exception.
     */
    const char* what() const throw();
};


#endif //EX4_FINAL_CLIENTDISCONNETEDEXCEPTION_H
