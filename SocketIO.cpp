#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
#include "SocketIO.h"

#include <chrono>
#include <thread>

#include "ClientDisconnetedException.h"

/**
 * @class SocketIO
 * @brief Handles read and write operations on a client socket
 */
/**
* @brief Constructor for the SocketIO class
* @param client_sock The client socket descriptor
*/
SocketIO::SocketIO(int client_sock) {
    client_socket = client_sock;
}
/**
 * @brief Reads data from the client socket
 * @return The data read from the socket
 * @throws ClientDisconnetedException If the client disconnects while reading
 */
std::string SocketIO::read() {
    char buffer[4096];
    try {


        int bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
        if (bytes_received <= 0) {
            throw ClientDisconnetedException("could not read");
        }

        std::string msg(buffer);
        return msg;
    }
    catch (std::exception&) {
        throw ClientDisconnetedException("could not read");
    }
}

void SocketIO::write(std::string data) {
    sendMutex.lock();
    try {
        int res = send(client_socket, data.c_str(), data.length(), 0);
        if (res <= 0) {
            throw ClientDisconnetedException("could not write");
        }
    } catch (std::exception&) {
        throw ClientDisconnetedException("could not write");
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(68));
    sendMutex.unlock();
}