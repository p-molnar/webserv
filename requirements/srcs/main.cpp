#include "../includes/WebServer.hpp"
#include <iostream>
#include <vector>
#include <sys/socket.h>

int main() 
{
    ServerSocket serverSocket;
    WebServer server;

    if (serverSocket.bindPort(8080) != EXIT_SUCCESS) {
        std::cerr << "Failed to bind to port" << std::endl;
        return 1;
    }
    if (serverSocket.listenPort(10) != EXIT_SUCCESS) {
        std::cerr << "Failed to listen on socket" << std::endl;
        return 1;
    }
    std::cout << "Server is listening on port 8080..." << std::endl;
    
    server.addFdToPollManager(serverSocket.getServerFd(), POLLIN);
    while (true)
    {
        try {
            server.pollClients();
        }
        catch (const std::runtime_error& e)
        {
            std::cerr << "Error occured during polling: " << e.what();
            break ;
        }
    }

    return 0;
}
