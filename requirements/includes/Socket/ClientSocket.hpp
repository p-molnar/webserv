#ifndef CLIENTSOCKET_HPP
#define CLIENTSOCKET_HPP

#include "Socket.hpp"
#include "errors.hpp"
#include "Log.hpp"
#include "httpRequest.hpp"
#include "httpResponse.hpp"

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
    httpResponse response;

private:
    std::string _request_buff;

public:

    enum class State { Reading, Writing } state = State::Reading;

    ClientSocket(int fd);
    ~ClientSocket(void);

    void setState(State newState) { state = newState; }
    State getState() const { return state; }

    const httpRequest& getRequest() const { return request; }
    httpResponse& getResponse() { return response; }
    std::string getRequestBuff() const { return this->_request_buff; }

    void recvRequest();
    void sendResponse();

};

#endif