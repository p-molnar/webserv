#include "WebServer.hpp"
#include <iostream>
#include <vector>
#include <sys/socket.h>

int main(int argc, char* argv[])
{
	Config config(argc, argv);
	config.display();	// temp for testing

    try
    {
        ServerSocket serverSocket;
        WebServer server;
        // serverSocket.bindPort(8080); // old
		serverSocket.bindPort(config.serverBlock.getListenPort());
        serverSocket.listenPort(10);
        ClientSocket clientSocket = serverSocket.acceptConnection();
        server.addFdToPollManager(serverSocket.getServerFd(), POLLIN);
        // server.pollClients(); // disabled because the function does not exist
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
