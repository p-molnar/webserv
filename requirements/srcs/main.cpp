#include "WebServer.hpp"

int main(int argc, char* argv[])
{
    try
    {
		Config config(argc, argv);
        ServerSocket serverSocket;
        WebServer server;
		serverSocket.loadConfig(config);
		serverSocket.config->display();
		return (0);
		// Todo: check if server[0] exists
        serverSocket.bindPort(serverSocket.config->getServers()[0].getListenPort()); // new
        // serverSocket.bindPort(8080); // old
        serverSocket.listenPort(10);
        ClientSocket clientSocket = serverSocket.acceptConnection();
        // server.addFdToPollManager(serverSocket.getServerFd(), POLLIN);
        // server.pollClients(); // disabled because the function does not exist
    }
    catch (const std::exception &e)
    {
        Log::logMsg(e.what());
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
