#ifndef SERVERSOCKET_HPP
#define SERVERSOCKET_HPP

#include <sys/types.h>  // Contains definitions for a number of data types used in system calls
#include <sys/socket.h> // Main sockets header
#include <netinet/in.h> // Contains constants and structures needed for internet domain addresses
#include <unistd.h>     // Provides access to the POSIX operating system API
#include <cstring>      // For memset
#include <iostream>     // For basic I/O
#include <stdexcept>    // For error handling, and to throw exceptions
#include <cerrno>       // Defines a set of string errors
#include <errors.hpp>
#include "ASocket.hpp"
#include <fcntl.h>
#include "Log.hpp"
#include "ClientSocket.hpp"

class ServerSocket : public ASocket
{
public:
    ServerSocket();
    ServerSocket(const ASocket &obj);
    ~ServerSocket();

public:
    t_socketType getType() const;

public:
    void bindPort(int port);
    void listenPort(int backlog);
    void recvRequest();
    void sendResponse();
    ClientSocket *acceptConnection();
};

#endif