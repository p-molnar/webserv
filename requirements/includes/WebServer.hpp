#ifndef WEBSERV_HPP
#define WEBSERV_HPP


#include "Socket/ClientSocket.hpp"
#include "Socket/ServerSocket.hpp"
#include "Socket/Socket.hpp"
#include "PollManager.hpp"

#include "httpRequest.hpp"
#include "Config.hpp"
#include "Parcer.hpp"

#include <vector>
#include <map>

class WebServer : public ServerSocket, public PollManager
{

private:
    // temporary solution for server configuration
    std::map<int, int> server_configs;

    std::vector<ServerSocket *> server_sockets;
    PollManager poll_manager;

    // constructor & destructor
public:
    WebServer();
    ~WebServer();

    // main member functions
public:
	Config config;
    void loadConfig(Config &config);
    void startService();

    static int getServerFd();
};

#endif