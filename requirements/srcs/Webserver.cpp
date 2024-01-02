#include "WebServer.hpp"
#include <stdexcept>
#include "ServerSocket.hpp"

WebServer::WebServer(){};

void WebServer::loadConfig(){
    // load parsed configuration file;
};

void WebServer::startService()
{
    server_socket.bindPort(8080);
    server_socket.listenPort(10);
    std::cout << "server socket: " << server_socket.getFd() << '\n';
    poll_manager.addServerFd(server_socket.getFd());
    poll_manager.pollRequests();
}

WebServer::~WebServer() {}