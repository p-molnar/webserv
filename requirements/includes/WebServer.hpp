#ifndef WEBSERV_HPP
#define WEBSERV_HPP

#include "ServerSocket.hpp"
#include "ClientSocket.hpp"
#include "PollManager.hpp"
#include "Config.hpp"
#include "Parcer.hpp"

#include <vector>
#include <map>
#include <memory>

class WebServer
{
private:
    PollManager _pollManager;
    std::map<int, std::shared_ptr<ServerSocket> > _activeServer;
    std::map<int, std::shared_ptr<ClientSocket> > _activeClients;

public:
    WebServer(){};
    ~WebServer(){};

    void addFdToPollManager(int fd, short events);
    void pollClients();
};

#endif