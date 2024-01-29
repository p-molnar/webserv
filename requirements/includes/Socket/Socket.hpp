#ifndef SOCKET__HPP
#define SOCKET__HPP

#include <sys/poll.h>
#include <stdexcept>
#include <unistd.h>

typedef struct pollfd t_pollfd;

class Socket
{
protected:
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

	// public:
	void setFd(int fd);
	void setPfd(t_pollfd pfd);
};

#endif
