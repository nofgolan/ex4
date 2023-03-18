#ifndef ASS4_SOCKETIO_H
#define ASS4_SOCKETIO_H

#include <string>
#include "DefaultIO.h"
#include <vector>
#include <mutex>


class SocketIO : public DefaultIO {
private:
    int client_socket; // the client socket descriptor
    std::mutex sendMutex; // so that no two threads can send too frequently
    std::vector<std::string> msgQ; // Queue to hold messages that need to be sent
public:
    /**
  * @brief Constructor
  * @param client_sock - The socket descriptor for the client
  */
    SocketIO(int client_sock);
    /**
       * @brief Read data from the client socket
       * @return The read data as a string
       * @throws ClientDisconnectedException if there is an error reading from the socket
       */
    std::string read() override;
    /**
      * @brief Write data to the client socket
      * @param data - The data to be written as a string
      * @throws ClientDisconnectedException if there is an error writing to the socket
      */
    void write(std::string) override;
};


#endif //ASS4_SOCKETIO_H
