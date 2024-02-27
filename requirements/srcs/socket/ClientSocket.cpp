/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ClientSocket.cpp                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: tklouwer <tklouwer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/26 12:14:17 by tklouwer      #+#    #+#                 */
/*   Updated: 2024/02/27 16:53:28 by tklouwer      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ClientSocket.hpp"

ClientSocket::ClientSocket(int fd, std::shared_ptr<ServerBlock> config) : request(config), response()
{
    this->fd = fd;
    this->pfd = (t_pollfd){fd, POLLIN, 0};
    this->config = config;
    this->last_activity = std::chrono::steady_clock::now();
}

ClientSocket::~ClientSocket()
{
    ::close(fd);
}

void    ClientSocket::updateLastActivity()
{
    last_activity = std::chrono::steady_clock::now();
}

bool    ClientSocket::hasTimedOut()
{
    auto now = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - last_activity);
    return elapsed.count() > SOCKET_TIMEOUT;
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
    if (hasTimedOut()) // TO DO CHECK TIMED OUT
        throw HttpRequest::requestTimedOut();
    setConnection(request.getHeaderComp("Connection"));
    Log::logMsg("request received", fd);
    if (is_request_parsed)
    {
        request.printParsedContent();
        request.safeUserData();
        setState(State::Writing);
    }
}

void ClientSocket::sendResponse()
{
    if (!is_request_parsed)
    {
        return;
    }
    std::string _response = response.generateResponse(request);
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
