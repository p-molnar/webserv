#ifndef SERVERSOCKET_HPP
#define SERVERSOCKET_HPP

#include <sys/socket.h>
#include <netinet/in.h>
#include <stdexcept>
#include <fcntl.h>

#include "ASocket.hpp"
#include "Log.hpp"
#include "ClientSocket.hpp"
#include "errors.hpp"

class ServerSocket : public ASocket
{
public:
    ServerSocket();
    ServerSocket(const ASocket &obj);
    ~ServerSocket();

public:
    t_socketType getType() const;

public:
    void createSocket();
    void bindPort(int port);
    void listenPort(int backlog);
    void recvRequest();
    void sendResponse();
    ClientSocket *acceptConnection();
};

#endif