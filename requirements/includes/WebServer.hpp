#ifndef WEBSERV_HPP
#define WEBSERV_HPP

#include "Socket/ClientSocket.hpp"
#include "Socket/ServerSocket.hpp"
#include "Socket/Socket.hpp"
#include "PollManager.hpp"

#include "HttpRequest.hpp"
#include "Config.hpp"

#include <memory>
#include <vector>
#include <map>


Config *g_config;

class WebServer : public ServerSocket, public PollManager
{

private:
    // Config *config;
    std::vector<std::shared_ptr<ServerSocket>> server_sockets;
    PollManager poll_manager;

    // constructor & destructo
public:
    WebServer();
    // WebServer(Config *config_data);
    ~WebServer();

    // main member functions
public:
    void startService();
};

#endif