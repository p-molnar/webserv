#ifndef SOCKET__HPP
#define SOCKET__HPP

#include <sys/poll.h>
#include <stdexcept>
#include <unistd.h>

typedef enum e_SocketType
{
	SERVER = 1,
	CLIENT
} t_socketType;

typedef struct pollfd t_pollfd;

class ASocket
{
protected:
	int fd;
	t_pollfd pfd;

public:
	ASocket();
	ASocket(int fd);
	ASocket(const ASocket &obj);
	virtual ~ASocket();

public:
	int getFd() const;
	t_pollfd getPfd() const;

	// public:
	void setFd(int fd);
	void setPfd(t_pollfd pfd);

public:
	virtual void recvRequest();
	virtual void sendResponse();

public:
	void close() const;

public:
	virtual t_socketType getType() const = 0;
};

#endif
