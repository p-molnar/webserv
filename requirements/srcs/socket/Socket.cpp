#include "Socket.hpp"

Socket::Socket() {}

Socket::Socket(int fd)
	: fd(fd),
	  pfd((t_pollfd){fd, POLLIN, 0})
{
}

Socket::Socket(const Socket &obj)
{
	this->fd = obj.fd;
	this->pfd = obj.pfd;
}

Socket::~Socket()
{
	if (fd >= 0)
		::close(fd);
}

int Socket::getFd() const { return fd; }

t_pollfd Socket::getPfd() const { return pfd; }

void Socket::setFd(int fd)
{
	this->fd = fd;
}

void Socket::setPfd(t_pollfd pfd)
{
	this->pfd = pfd;
}