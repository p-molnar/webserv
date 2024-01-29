#include "WebServer.hpp"
#include <stdexcept>
#include "ServerSocket.hpp"

WebServer::WebServer(){};

void WebServer::loadConfig(Config &config_data)
{
	config = &config_data;
    // load parsed configuration file;

    // tmp stuff
    // server_configs[8000] = 10;
    // server_configs[8001] = 10;
    // server_configs[8002] = 10;
    server_configs[8080] = 10;
};

// void ServerSocket::loadConfig(Config& config_data)
// {
// 	config = &config_data;
// }

void WebServer::startService()
{
    Log::logMsg("Server started");
    for (std::pair<int, int> config : server_configs)
    {
        int port = config.first;
        int backlog = config.second;

        std::shared_ptr<ServerSocket> server_socket = std::shared_ptr<ServerSocket>(new ServerSocket());

        server_socket->createSocket();
        server_socket->bindPort(port);
        server_socket->listenPort(backlog);
        poll_manager.addSocket(server_socket);
        server_sockets.push_back(server_socket);
    }
    poll_manager.processEvents();
}

WebServer::~WebServer()
{
    Log::logMsg("Server(s) shutdown");
}
