#include "WebServer.hpp"
#include <stdexcept>
#include "ServerSocket.hpp"

WebServer::WebServer() : srv_socket(new ServerSocket){};

void WebServer::loadConfig(){
    // load parsed configuration file;
};

void WebServer::startService()
{
    srv_socket->bindPort(8080);
    srv_socket->listenPort(10);
    poll_manager.addSocket(srv_socket);
    poll_manager.pollRequests();
}

WebServer::~WebServer()
{
    delete srv_socket;
}