#ifndef CLIENTSOCKET_HPP
#define CLIENTSOCKET_HPP

#include "Socket.hpp"
#include "errors.hpp"
#include "Log.hpp"
#include "httpRequest.hpp"

#include <sys/poll.h>
#include <sys/socket.h>
#include <stdexcept>
#include <exception>

class ClientSocket : public Socket
{
public:
    class HungUpException : public std::exception
    {
        std::string exc;

    public:
        HungUpException(){};
        HungUpException(std::string what_arg) : exc(what_arg){};
        const char *what() const throw() { return exc.c_str(); };
        ~HungUpException() throw(){};
    };

private:
    bool request_parsed;
    httpRequest request;

public:
    ClientSocket(int fd);
    ~ClientSocket(void);

public:
    void recvRequest();
    void sendResponse();
};

#endif