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
        std::string exc;

    public:
        HungUpException() : exc(""){};
        HungUpException(std::string what_arg) : exc(what_arg){};
        const char *what() const throw() { return exc.c_str(); };
        ~HungUpException() throw(){};
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