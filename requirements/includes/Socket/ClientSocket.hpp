#ifndef CLIENTSOCKET_HPP
#define CLIENTSOCKET_HPP

#include <stdexcept>
#include <exception>

#include "Socket.hpp"
#include "errors.hpp"
#include "Log.hpp"
#include "HttpRequest.hpp"
#include "SysCall.hpp"

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
    HttpRequest request;

private:
    bool isReadyToRead;
    bool isReadyToWrite;

    std::string _request_buff;
    std::string _response;

public:
    ClientSocket(int fd);
    ~ClientSocket(void);

    std::string getRequestBuff() const { return this->_request_buff; }

    HttpRequest recvRequest();
    void sendResponse();

    void setReadyToRead(bool ready) { isReadyToRead = ready; }
    bool getReadyToRead() const { return isReadyToRead; }

    void setReadyToWrite(bool ready) { isReadyToWrite = ready; }
    bool getReadyToWrite() const { return isReadyToWrite; }

    void setResponse(std::string response);
};

#endif