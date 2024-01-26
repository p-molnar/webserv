#ifndef WEBSERV_HPP
#define WEBSERV_HPP

#include "ServerSocket.hpp"
#include "ClientSocket.hpp"
#include "PollManager.hpp"
#include "Config.hpp"
#include "Parcer.hpp"

#include <memory>
#include <vector>
#include <map>

class WebServer : public ServerSocket, public PollManager
{

private:
    // temporary solution for server configuration
    std::map<int, int> server_configs;

    std::vector<std::unique_ptr<ServerSocket>>server_sockets; // Changed to UNIQUE_PTR
    PollManager poll_manager;

    // constructor & destructor
public:
    WebServer();
    ~WebServer();

    // main member functions
public:
    void loadConfig();
    void startService();

    static int getServerFd();
};

#endif