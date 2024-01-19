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
    bool is_request_parsed;
    httpRequest request;

private:
    bool isReadyToRead;
    bool isReadyToWrite;

    std::string _request_buff;
    std::string _response;

public:
    ClientSocket(int fd);
    ~ClientSocket(void);

    const httpRequest& getRequest() const { return request; }
    std::string getRequestBuff() const { return this->_request_buff; }

    void recvRequest();
    void sendResponse();

    void setReadyToRead(bool ready) { isReadyToRead = ready; }
    bool getReadyToRead() const { return isReadyToRead; }

    void setReadyToWrite(bool ready) { isReadyToWrite = ready; }
    bool getReadyToWrite() const { return isReadyToWrite; }

    void setResponse(std::string response);
};

#endif