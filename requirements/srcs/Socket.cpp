#include "Socket.hpp"

Socket::Socket(int fd, socketType type)
	: fd(fd), type(type)
{
}

Socket::Socket(const Socket &obj) : fd(obj.fd), type(obj.type) {}

Socket Socket::operator=(const Socket &obj)
{
	this->fd = obj.fd;
	this->type = obj.type;
	return *this;
}

Socket::~Socket() {}

int Socket::getFd() { return fd; }
socketType Socket::getType() { return type; }