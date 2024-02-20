#ifndef SOCKET__HPP
#define SOCKET__HPP

#include "Config.hpp"

#include <sys/poll.h>
#include <stdexcept>
#include <unistd.h>
#include <memory>

typedef struct pollfd t_pollfd;

class Socket
{
protected:
	std::shared_ptr<ServerBlock> config;
	int fd;
	t_pollfd pfd;

public:
	Socket();
	Socket(int fd);
	Socket(const Socket &obj);
	virtual ~Socket();

public:
	int getFd() const;
	t_pollfd getPfd() const;
};

#endif
