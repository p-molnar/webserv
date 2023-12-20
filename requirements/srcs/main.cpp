#include "WebServer.hpp"
#include <iostream>
#include <vector>
#include <sys/socket.h>

int main()
{
    try
    {
        ServerSocket serverSocket;
        WebServer server;
        serverSocket.bindPort(8080);
        serverSocket.listenPort(10);
        ClientSocket clientSocket = serverSocket.acceptConnection();
        server.addFdToPollManager(serverSocket.getServerFd(), POLLIN);
        server.pollClients();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
