#ifndef SERVERSOCKET_HPP
#define SERVERSOCKET_HPP

#include <netinet/in.h>
#include <stdexcept>
#include <memory>

#include "Socket.hpp"
#include "Log.hpp"
#include "ClientSocket.hpp"
#include "errors.hpp"
#include "Config.hpp"
#include "SysCall.hpp"

class ServerSocket : public Socket
{
private:
    // Config *config;

public:
    ServerSocket();
    ServerSocket(const Socket &obj);
    ~ServerSocket();

public:
    void createSocket();
    void bindPort(int port);
    void listenPort(int backlog, int port);
    void recvRequest();
    void sendResponse();
    std::shared_ptr<ClientSocket> acceptConnection();
};

#endif