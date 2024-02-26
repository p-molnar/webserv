/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Socket.cpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tklouwer <tklouwer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/26 12:14:52 by tklouwer      #+#    #+#                 */
/*   Updated: 2024/02/26 12:14:53 by tklouwer      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Socket.hpp"

Socket::Socket() {}

Socket::Socket(int fd)
	: fd(fd),
	  pfd((t_pollfd){fd, POLLIN, 0})
{
}

Socket &Socket::operator=(const Socket &obj)
{
	this->fd = obj.fd;
	this->pfd = obj.pfd;
	this->config = obj.config;
	return *this;
}

Socket::Socket(const Socket &obj)
{
	this->fd = obj.fd;
	this->pfd = obj.pfd;
	this->config = obj.config;
}

Socket::~Socket()
{
	if (fd >= 0)
		::close(fd);
}

int Socket::getFd() const { return fd; }

t_pollfd Socket::getPfd() const { return pfd; }
