#include "ClientSocket.hpp"
#include "consts.hpp"

ClientSocket::ClientSocket(int fd)
{
    this->setFd(fd);
    this->setPfd((t_pollfd){fd, POLLIN, 0});
    isReadyToRead = false;
    isReadyToWrite = false;
}

ClientSocket::~ClientSocket()
{
    ::close(fd);
}

HttpRequest ClientSocket::recvRequest()
{
    char request_buff[10240]; // 10kb buffer size
    int bytes_received = recv(fd, request_buff, sizeof(request_buff), 0);

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

    is_request_parsed = request.parseRequest(request_buff, bytes_received);
    Log::logMsg("request received", fd);
    return (request);
}

void ClientSocket::sendResponse()
{
    if (!is_request_parsed)
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
    is_request_parsed = false;
    Log::logMsg("response sent", fd);
}