#ifndef WEBSERV_HPP
#define WEBSERV_HPP

#include "Socket/ClientSocket.hpp"
#include "Socket/ServerSocket.hpp"
#include "Socket/Socket.hpp"
#include "PollManager.hpp"
#include "httpStatus.hpp"
#include "HttpRequest.hpp"
#include "Config.hpp"

#include <memory>
#include <vector>
#include <map>

class WebServer : public ServerSocket, public PollManager
{

private:
    std::shared_ptr<Config> config;
    std::vector<std::shared_ptr<ServerSocket>> server_sockets;
    PollManager poll_manager;

    // constructor & destructo
public:
    WebServer(std::shared_ptr<Config> config);
    ~WebServer();

    // main member functions
public:
    void ServerSocketloadConfig();
    void startService();
    void loadConfig(Config &config_data);

    static int getServerFd();
};

#endif