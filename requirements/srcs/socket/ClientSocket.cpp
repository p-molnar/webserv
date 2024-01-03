#include "ClientSocket.hpp"

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
            throw std::runtime_error("recv: " + STRERR);
        }
    }
    Log::logMsg("Request received for client with fd " + std::to_string(fd));
}

void ClientSocket::sendResponse()
{
    // std::cout << "\nREQUEST:\n"
    //           << request_buff
    //           << "REQUEST END\n";
    std::string response_body = "\r\n\r\nOK";
    std::string response_header = "HTTP/1.1 200 OK";
    response_header += "\nContent-length:2";

    std::string response = response_header + response_body;

    int bytes_sent = send(fd, response.c_str(), response.size(), 0);

    if (bytes_sent < 0)
    {
        throw std::runtime_error("accept: " + STRERR);
    }
    Log::logMsg("Response send to client with fd " + std::to_string(fd));
}