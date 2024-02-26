/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ClientSocket.hpp                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: tklouwer <tklouwer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/26 12:08:05 by tklouwer      #+#    #+#                 */
/*   Updated: 2024/02/26 12:08:06 by tklouwer      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENTSOCKET_HPP
#define CLIENTSOCKET_HPP

/* C/C++ Libs */
#include <stdexcept>
#include <exception>

/* Webserv */
#include "Socket.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "errors.hpp"
#include "Log.hpp"
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
    HttpResponse response;

private:
    std::string _request_buff;

public:
    enum class State
    {
        Reading,
        Writing
    } state = State::Reading;

    ClientSocket(int fd, std::shared_ptr<ServerBlock> config);
    ~ClientSocket(void);

    void setState(State newState) { state = newState; }
    State getState() const { return state; }

    const HttpRequest &getRequest() const { return request; }
    HttpResponse &getResponse() { return response; }
    std::string getRequestBuff() const { return this->_request_buff; }

    void recvRequest();
    void sendResponse();
    void sendResponse(std::string response); // Overloading the send response function for error usage.
};

#endif