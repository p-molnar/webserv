#ifndef SERVERSOCKET_HPP
#define SERVERSOCKET_HPP

#include <sys/socket.h>
#include <netinet/in.h>
#include <stdexcept>
#include <fcntl.h>

#include "Socket.hpp"
#include "Log.hpp"
#include "ClientSocket.hpp"
#include "errors.hpp"
#include "Config.hpp"

class ServerSocket : public Socket
{
public:
    ServerSocket();
    ServerSocket(const Socket &obj);
    ~ServerSocket();

public:
	Config *config;
	void loadConfig(Config &config);
    void createSocket();
    void bindPort(int port);
    void listenPort(int backlog);
    void recvRequest();
    void sendResponse();
    ClientSocket *acceptConnection();
};

#endif