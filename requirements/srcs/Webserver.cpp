#include "WebServer.hpp"
#include <stdexcept>
#include "ServerSocket.hpp"

WebServer::WebServer(){};

void WebServer::loadConfig()
{
    // load parsed configuration file;

    // tmp stuff
    // server_configs[8000] = 10;
    // server_configs[8001] = 10;
    // server_configs[8002] = 10;
    server_configs[8080] = 10;
};

void WebServer::startService()
{
    Log::logMsg("Server started");
    for (std::pair<int, int> config : server_configs)
    {
        int port = config.first;
        int backlog = config.second;

        ServerSocket *server_socket = new ServerSocket;
        server_sockets.push_back(server_socket);

        server_socket->createSocket();
        server_socket->bindPort(port);
        server_socket->listenPort(backlog);
        poll_manager.addSocket(server_socket);
    }
    poll_manager.pollRequests();
}

WebServer::~WebServer()
{
    for (ServerSocket * socket : server_sockets)
        delete socket;
    Log::logMsg("Server(s) shutdown");
}