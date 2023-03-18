#include <iostream>
#include <poll.h>
#include <string>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <chrono>
#include <thread>
#include <fstream>
#include <sstream>
#include <cstring>
#include <vector>
#include <algorithm>  // for std::find
#include "PreProcess.h"

const int BUFFER_SIZE = 4096;

// Struct to store the socket descriptor and the filename for the download worker thread
struct downloadArgs {
    int sock;
    std::string filename;
};

/**
 * @brief      Thread function that receives data from the server over the socket and writes it to a file.
 * @param[in]  args  struct containing the socket descriptor and the filename
 */
void downloadingWorker(struct downloadArgs args) {
// Open the file with the specified filename
    std::ofstream myfile(args.filename);
// If the file cannot be opened, print an error message
    if (!myfile.is_open()) {
        std::cerr << "downloader thread could not write file!" << std::endl;
    }

    char buffer[BUFFER_SIZE];

    while (true) {
        // Peek at the next message from the server, but do not remove it from the queue
        size_t bytes_received = recv(args.sock, buffer, BUFFER_SIZE, MSG_PEEK);
        // If there was an error receiving the message, print an error message and exit
        if (bytes_received <= 0) {
            std::cerr << "Error: Downloader thread unable to receive message from server" << std::endl;
            exit(2);
        }
        // Convert the received data to a string
        std::string msg(buffer, bytes_received);
        // Check if the message starts with "@@@"
        if (msg.rfind("@@@", 0) == 0) {
            // Receive the full message from the server
            size_t n = recv(args.sock, buffer, BUFFER_SIZE, 0);
            // If the number of bytes received is not the same as the number of bytes peeked, print an error message and exit
            if (n != bytes_received) {
                std::cerr << "Error: Error trying to receive message from server" << std::endl;
                exit(2);
            }
            // If the file is open
            if (myfile.is_open()) {
                // If the message is "@@@ done", break out of the loop
                if (msg == "@@@ done") break;
                // If the message starts with "@@@ append: ", write the rest of the message to the file
                const std::string start_append = "@@@ append: ";
                const char *line = msg.c_str() + start_append.length();
                myfile << std::string(line) << std::endl;
            }
        }
    }
    // Close the file
    myfile.close();
}

void sendToServer(std::string message, int sock) {
    if (send(sock, message.c_str(), message.length() + 1, 0) < 0) {
        std::cerr << "Error: Unable to send message to server" << std::endl;
        exit(1);
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(68));
}

/**
 * @brief      Sends a message to the server over the socket
 * @param[in]  message  The message to send
 * @param[in]  sock     The socket descriptor
 */
void openFile(std::string &path, int sock) {
    std::ifstream file(path);
    if (!file.good()) {
        std::stringstream ss;
        ss << "<<Error: the file '" << path << "' does not exist.";
        std::string msg = ss.str();
        sendToServer(msg, sock);
        return;
    }
    if (!file.is_open()) {
        std::string msg = "<<Error opening file\n";
        sendToServer(msg, sock);
        return;
    }
    char buffer[BUFFER_SIZE];
    std::string line;
    while (std::getline(file, line)) {
        sendToServer(line, sock);
        size_t bytes_received = recv(sock, buffer, BUFFER_SIZE, 0);
        if (bytes_received <= 0) {
            std::cerr << "Error: Downloader thread unable to receive message from server" << std::endl;
            exit(2);
        }
        std::string msg(buffer, bytes_received);
        if (msg == "%%error") {
            return;
        }
    }
    std::string msg = ">>end";
    sendToServer(msg, sock);
    file.close();
}

/**
 * commands function is responsible for handling different commands from the user
 * @param command the string that contains the command
 * @param sock the socket descriptor for the connection
 * @param download pointer to the thread that is used for downloading
 */
void commands(std::string &command, int sock, std::thread *download) {
    // Constants for the start of the command
    const std::string start_send_me = "<<send me ";
    const std::string start_download = "<<download ";
    // Check if the command starts with "<<send me "
    if (command.rfind(start_send_me, 0) == 0) {
        // Get the path by removing the "<<send me " prefix
        const char *path = command.c_str() + start_send_me.length();
        // Convert the path to a string
        std::string path_str(path);
        // Call the openFile function with the path and the socket
        openFile(path_str, sock);
    }
        // Check if the command starts with "<<download "
    else if (command.rfind(start_download, 0) == 0) {
        // Get the path by removing the "<<download " prefix
        const char *path = command.c_str() + start_download.length();
        // Convert the path to a string
        std::string path_str(path);
        // Create a struct for the download arguments
        struct downloadArgs args = {sock, path_str};
        // Create a new thread for the downloading worker
        download = new std::thread(downloadingWorker, args);
    }
}


int main(int argc, char *argv[]) {

    std::thread *download = nullptr;
    // Check for the correct number of command line arguments
    if (argc != 3) {
        std::cerr << "Not enough arguments" << std::endl;
        return 1;
    }

    // Read the IP address and port number from the command line arguments
    std::string ip_address = argv[1];
    int port = std::stoi(argv[2]);
    char *ip = &ip_address[0];

    struct sockaddr_in sa{};
    int resulty = inet_pton(AF_INET, ip, &(sa.sin_addr));
    if (resulty != 1) {
        std::cerr << "Invalid IP address: " << ip_address << std::endl;
        return 1;
    }

    // Create a socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) { // if socket was not created exit the program.
        return 1;
    }

    // Connect to the server
    sockaddr_in serv_addr{};
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    serv_addr.sin_addr.s_addr = inet_addr(ip_address.c_str());
    // connect to server results.
    if (connect(sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        std::cerr << "Error: Unable to connect to server" << std::endl;
        return 1;
    }
    // Set up poll
    struct pollfd fds[2];
    fds[0].fd = sock;
    fds[0].events = POLLIN;
    fds[1].fd = STDIN_FILENO;
    fds[1].events = POLLIN;
    char buffer[BUFFER_SIZE];
    // Main loop
    while (true) {
        if (poll(fds, 2, -1) < 0) {
            std::cerr << "Error: Unable to poll" << std::endl;
            return 1;
        }

        if (fds[0].revents & POLLIN) {
            // Received message from server
            size_t bytes_received = recv(sock, buffer, BUFFER_SIZE, MSG_PEEK);
            if (bytes_received <= 0) {
                std::cerr << "Error: Unable to receive message from server" << std::endl;
                return 1;
            }

            std::string msg(buffer, bytes_received);

            if (msg.rfind("@@@", 0) != 0) {
                // if msg doesn't start with @@@, it's for us! pop it from the queue.
                size_t n = recv(sock, buffer, BUFFER_SIZE, 0);
                if (n != bytes_received) {
                    std::cerr << "Error: Error trying to receive message from server" << std::endl;
                    return 1;
                }
                if (msg.length() >= 2 && msg[0] == '<' && msg[1] == '<') {
                    commands(msg, sock, download);
                } else {
                    std::cout << msg << std::endl;
                }
            } else {
//                std::cout << "main thread ignoring " << msg << std::endl;
            }
        }

        if (fds[1].revents & POLLIN) {
            // User entered message
            std::string message;
            std::getline(std::cin, message);
            if (message == "8") break;
            sendToServer(message, sock);
        }
    }
    if (download != nullptr) {
        std::cout << "will close as soon as the download finishes" << std::endl;
        download->join();
        delete download;
    }
    close(sock);
    return 0;
}
