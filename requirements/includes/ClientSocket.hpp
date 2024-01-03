#ifndef CLIENTSOCKET_HPP
#define CLIENTSOCKET_HPP

#include "ASocket.hpp"
#include "errors.hpp"
#include "Log.hpp"

#include <sys/poll.h>
#include <sys/socket.h>
#include <stdexcept>

class ClientSocket : public ASocket
{
    class HungUpException : public std::exception
    {
    public:
        HungUpException(){};
    };

private:
    char request_buff[2048];

public:
    ClientSocket(int fd);
    ~ClientSocket(void);

public:
    t_socketType getType() const;
    void recvRequest();
    void sendResponse();
};

#endif