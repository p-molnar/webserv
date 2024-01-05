#ifndef CLIENTSOCKET_HPP
#define CLIENTSOCKET_HPP

#include "ASocket.hpp"
#include "errors.hpp"
#include "Log.hpp"

#include <sys/poll.h>
#include <sys/socket.h>
#include <stdexcept>
#include <exception>

class ClientSocket : public ASocket
{
public:
    class HungUpException : public std::exception
    {
    public:
        HungUpException(){};
    };

    class OtherErrException : public std::exception
    {
    public:
        OtherErrException(){};
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