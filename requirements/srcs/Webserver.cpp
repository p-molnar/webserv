#include "WebServer.hpp"
#include <stdexcept>
#include "ServerSocket.hpp"

WebServer::WebServer(){};

void WebServer::loadConfig(Config *config_data)
{
    config = config_data;
}

void WebServer::startService()
{
    Log::logMsg("Server started");
    for (ServerBlock config : config->getServers())
    {
        int port = config.getListenPort();
        int backlog = 10;

        std::shared_ptr<ServerSocket> server_socket = std::shared_ptr<ServerSocket>(new ServerSocket());

        server_socket->createSocket();
        server_socket->bindPort(port);
        server_socket->listenPort(backlog, port);
        poll_manager.addSocket(server_socket);
        server_sockets.push_back(server_socket);
    }
    poll_manager.processEvents();
}

WebServer::~WebServer()
{
    Log::logMsg("Server(s) shutdown");
}
