#include "ClientSocket.hpp"

ClientSocket::ClientSocket(int socketfd) : _clientfd(socketfd)
{
}

ClientSocket::~ClientSocket()
{
    ::close(this->_clientfd);
}

ssize_t ClientSocket::pullMessage(char *buffer, size_t length)
{
    return recv(_clientfd, buffer, length, 0);
}

ssize_t ClientSocket::sendMessage(const char *buffer, size_t length)
{
    return send(_clientfd, buffer, length, 0);
}

void ClientSocket::closeFd()
{
    close(_clientfd);
}