#ifndef CLIENTSOCKET_HPP
#define CLIENTSOCKET_HPP

#include <unistd.h>
#include <sys/select.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include "ASocket.hpp"
#include <stdexcept>
#include <cerrno>
#include <string>

class ClientSocket : public ASocket
{
public:
    ClientSocket(int fd);
    ~ClientSocket(void);

    void close(void);
};

#endif