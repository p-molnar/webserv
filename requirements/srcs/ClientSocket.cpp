#include "ClientSocket.hpp"

ClientSocket::ClientSocket(int fd)
{
    this->fd = fd;
}

ClientSocket::~ClientSocket()
{
    ::close(fd);
}

void ClientSocket::close()
{
    if (::close(fd) == -1)
    {
        throw std::runtime_error("ClientSocket::close " + std::string(strerror(errno)));
    }
}