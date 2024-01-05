#include "ClientSocket.hpp"
#include "consts.hpp"

ClientSocket::ClientSocket(int fd)
{
    this->setFd(fd);
    this->setPfd((t_pollfd){fd, POLLIN, 0});
}

ClientSocket::~ClientSocket()
{
    ::close(fd);
}

t_socketType ClientSocket::getType() const { return CLIENT; }

void ClientSocket::recvRequest()
{

    int bytes_received = recv(fd, request_buff, sizeof(request_buff), 0);
    if (bytes_received <= 0)
    {
        if (bytes_received == 0)
        {
            Log::logMsg("Client on fd " + std::to_string(fd) + " hung up");
            throw ClientSocket::HungUpException();
        }
        else
        {
            throw std::runtime_error(STRERR);
        }
    }
    Log::logMsg("Request received for client with fd " + std::to_string(fd));
}

void ClientSocket::sendResponse()
{
    std::string status_line = "HTTP/1.1 200 OK";
    std::string response_headers = "";
    response_headers += "Content-Type: text/html" + CRLF;
    response_headers += "Content-Length: 0" + CRLF;
    std::string response_body = "";

    std::string response = status_line +
                           CRLF +
                           response_headers +
                           CRLF +
                           response_body;

    int bytes_sent = send(fd, response.c_str(), response.size(), 0);

    if (bytes_sent < 0)
    {
        throw std::runtime_error("accept: " + STRERR);
    }
    Log::logMsg("Response send to client with fd " + std::to_string(fd));
}