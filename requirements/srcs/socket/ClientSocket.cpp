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

    request_parsed = request.parseRequest(request_buff);

    Log::logMsg("request received", fd);
    if (request_parsed)
        request.printParsedContent();
}

void ClientSocket::sendResponse()
{
    if (!request_parsed)
        return;

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
        request.flushBuffers();
        throw std::runtime_error("accept: " + STRERR);
    }
    request.flushBuffers();
    request_parsed = false;
    Log::logMsg("response sent", fd);
}