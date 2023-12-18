#include "../includes/WebServer.hpp"
#include <iostream>
#include <vector>
#include <sys/socket.h>

int main()
{
    ServerSocket serverSocket;
    WebServer server;
    try
    {
        serverSocket.bindPort(8080);
        serverSocket.listenPort(10);
        std::cout << "Server is listening on port 8080..." << std::endl;
        ClientSocket clientSocket = serverSocket.acceptConnection();
        std::cout << "Connection accepted" << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        return EXIT_FAILURE;
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
