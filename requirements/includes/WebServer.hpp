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
    std::vector<struct pollfd> pfds;

public:
    WebServer();

    void loadConfig();
    void startService();

    ~WebServer();

    void addPfd(int fd, short events);
    void removePfd(int fd);
    void pollClients();
};

#endif