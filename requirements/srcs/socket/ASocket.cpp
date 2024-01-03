#include "ASocket.hpp"

ASocket::ASocket() {}

ASocket::ASocket(int fd)
	: fd(fd),
	  pfd((t_pollfd){fd, POLLIN, 0})
{
}

ASocket::ASocket(const ASocket &obj)
{
	this->fd = obj.fd;
	this->pfd = obj.pfd;
}

ASocket::~ASocket()
{
	if (fd >= 0)
		::close(fd);
}

int ASocket::getFd() const { return fd; }

t_pollfd ASocket::getPfd() const { return pfd; }

void ASocket::setFd(int fd)
{
	this->fd = fd;
}

void ASocket::setPfd(t_pollfd pfd)
{
	this->pfd = pfd;
}

void ASocket::recvRequest() {}
void ASocket::sendResponse() {}

void ASocket::close() const
{
	if (fd < 0)
		throw std::runtime_error("close: attempt of closing negative fd");

	::close(fd);
}