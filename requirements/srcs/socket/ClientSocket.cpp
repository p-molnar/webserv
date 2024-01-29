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
    char request_buff[2048];
    int bytes_received = recv(fd, request_buff, sizeof(request_buff) - 1, 0);
    request_buff[bytes_received] = '\0';
    if (bytes_received <= 0)
    {
        request.flushBuffers();
        if (bytes_received == 0)
        {

            Log::logMsg("Connection hung up", fd);
            throw ClientSocket::HungUpException();
        }
        else
        {
            throw std::runtime_error(STRERR);
        }
    }
    is_request_parsed = request.parseRequest(request_buff);
    Log::logMsg("request received", fd);
    if (is_request_parsed)
        setState(State::Writing);
}

void ClientSocket::sendResponse()
{
    if (!is_request_parsed)
    {
        return;
    }
    std::string _response = response.generateResponse(true);
    std::cout << _response << std::endl;
    std::cout << _response.size() << std::endl;
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