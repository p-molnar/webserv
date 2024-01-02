#ifndef CLIENTSOCKET_HPP
#define CLIENTSOCKET_HPP

#include <unistd.h>
#include <sys/select.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <stdexcept>
#include <cerrno>
#include <string>
#include "Socket.hpp"

class ClientSocket : public Socket
{
public:
    ClientSocket(int fd);
    ~ClientSocket(void);

public:
    void close(void);
};

#endif