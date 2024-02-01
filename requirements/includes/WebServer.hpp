#ifndef WEBSERV_HPP
#define WEBSERV_HPP

#include "Socket/ClientSocket.hpp"
#include "Socket/ServerSocket.hpp"
#include "Socket/Socket.hpp"
#include "PollManager.hpp"

#include "HttpRequest.hpp"
#include "Config.hpp"
#include "Parcer.hpp"

#include <memory>
#include <vector>
#include <map>

class WebServer : public ServerSocket, public PollManager
{

private:
    Config *config;
    std::vector<std::shared_ptr<ServerSocket>> server_sockets;
    PollManager poll_manager;

    // constructor & destructor
public:
    WebServer();
    ~WebServer();

    // main member functions
public:
    void loadConfig(Config & config);
    void startService();

    static int getServerFd();
};

#endif