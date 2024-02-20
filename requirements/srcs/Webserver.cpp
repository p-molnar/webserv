#include "WebServer.hpp"
#include <stdexcept>
#include "ServerSocket.hpp"

WebServer::WebServer(std::shared_ptr<Config> config) : config(config){};

void WebServer::startService()
{

    std::vector<pid_t> pids;
    for (ServerBlock &config : config->getServers())
    {
        std::shared_ptr<ServerBlock> config_ptr = std::make_shared<ServerBlock>(config);
        try
        {
            std::shared_ptr<ServerSocket> server_socket = std::shared_ptr<ServerSocket>(new ServerSocket(config_ptr));
            Log::logMsg("Server started");
            server_socket->createSocket();
            server_socket->bindPort(config.getListenPort());
            server_socket->listenPort(10, config.getListenPort());
            poll_manager.addSocket(server_socket);
            server_sockets.push_back(server_socket);
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
            exit(EXIT_FAILURE); // rewrite with another function
        }
    }
    poll_manager.processEvents();
}

WebServer::~WebServer()
{
    Log::logMsg("Server(s) shutdown");
}
