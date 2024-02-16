#include "ClientSocket.hpp"
#include "consts.hpp"
#include <iostream>

ClientSocket::ClientSocket(int fd)
{
    this->setFd(fd);
    this->setPfd((t_pollfd){fd, POLLIN, 0});
}

ClientSocket::~ClientSocket()
{
    ::close(fd);
}

void ClientSocket::recvRequest()
{
    char request_buff[10240]; // 10kb buffer size
    int bytes_received = SysCall::recv(fd, request_buff, sizeof(request_buff), 0);

    if (bytes_received == 0)
    {
        request.flushBuffers();
        Log::logMsg("Connection hung up", fd);
        throw ClientSocket::HungUpException();
    }

    is_request_parsed = request.parseRequest(request_buff, bytes_received);
    Log::logMsg("request received", fd);
    if (is_request_parsed)
    {
        request.printParsedContent();
        setState(State::Writing);
    }
}

void ClientSocket::sendResponse()
{
    if (!is_request_parsed)
    {
        return;
    }
    std::string _response = response.generateResponse(request, true);
    std::cout << CGRY << _response << NC << std::endl; // Todo commend out
    int bytes_sent = send(fd, _response.c_str(), _response.size(), 0);
    if (bytes_sent < 0)
    {
        request.flushBuffers();
        throw std::runtime_error("accept: " + STRERR);
    }
    request.flushBuffers();
    is_request_parsed = false;
    Log::logMsg("response sent", fd);
    setState(State::Reading);
}

void ClientSocket::sendResponse(std::string response)
{
    if (!is_request_parsed)
    {
        return;
    }
    int bytes_sent = send(fd, response.c_str(), response.size(), 0);
    if (bytes_sent < 0)
    {
        request.flushBuffers();
        throw std::runtime_error("accept: " + STRERR);
    }
    request.flushBuffers();
    is_request_parsed = false;
    Log::logMsg("response sent", fd);
    setState(State::Reading);
}