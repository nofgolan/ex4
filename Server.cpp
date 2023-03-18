#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include "PreProcess.h"
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <pthread.h>
#include <stdlib.h>
#include <thread>
#include "Command3.h"
#include "SocketIO.h"
#include "CLI.h"
#include "ClientDisconnetedException.h"

#include <netinet/tcp.h>

using namespace std;

void handle_client(int client_socket) {
    SocketIO sio(client_socket);
    CLI cli(&sio);
    try {
        cli.start();
    }
    catch (ClientDisconnetedException& err) {
        // ignore
//std::cout << "client disconnected: " << err.what() << std::endl;
    }

}

int main(int argc, char *argv[]) {
    //Check the input.
    //Checking the user sent only two arguments.
    if (argc != 2) {
        std::cerr << "Error: Too many or not enough arguments." << std::endl;
        return 1;
    }
    // making sure the first input is a positive integer and can be used for port number.
    if (!positiveInteger(argv[1])) {
        std::cerr << "Error: first argument is not a positive integer." << std::endl;
        return 1;
    }
    // saving port number.
    const int server_port = stoi(argv[1]);
    if (server_port < 1024 || server_port > 65535) {
        std::cerr << "Error: cannot use this port." << std::endl;
        return 1;
    }

    //Creating socket.
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) { perror("error creating socket"); return 1; }

    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(server_port);
    //Bind.
    if (::bind(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
        perror("error binding socket");
    }
    //Listen
    if (listen(sock, 5) < 0) {
        perror("error listening to a socket");
    }
    struct sockaddr_in client_sin;
    unsigned int addr_len = sizeof(client_sin);
    while (true) {
        int client_sock = accept(sock, (struct sockaddr *) &client_sin, &addr_len);
        if (client_sock < 0) {
            perror("error accepting client");
        }
        // detach - thread will run without any care to the other threads.
        thread(handle_client, client_sock).detach();
    }
}