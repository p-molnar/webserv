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
    // The server configuration is identified by its port number
    // i.e., there should be a std::map<port, ServerConfig> server_configs that allows us
    // to get a server configuration based on its port number

    // tmp data structure while the ServerConfig parsed class is missing
    Log::logMsg("Server started");
    std::map<int, int>::iterator it = server_configs.begin();
    std::map<int, int>::iterator ite = server_configs.end();

    while (it != ite)
    {
        int port = it->first;
        int backlog = it->second;

        ServerSocket *server_socket = new ServerSocket;
        server_sockets.push_back(server_socket);

        server_socket->createSocket();
        server_socket->bindPort(port);
        server_socket->listenPort(backlog);
        poll_manager.addSocket(server_socket);
        it++;
    }
    poll_manager.pollRequests();
}

WebServer::~WebServer()
{
    for (size_t i = 0; i < server_sockets.size(); i++)
    {
        delete server_sockets[i];
    }
    Log::logMsg("Server(s) shutdown");
}