#ifndef WEBSERV_HPP
#define WEBSERV_HPP

#include "ServerSocket.hpp"
#include "ClientSocket.hpp"
#include "PollManager.hpp"

#include <vector>
#include <map>
#include <memory>

class WebServer : public ServerSocket, public PollManager
{

private:
    // Config config;
    ServerSocket server_socket;
    PollManager poll_manager;
    std::vector<struct pollfd> pfds;

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