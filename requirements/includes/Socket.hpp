#ifndef SOCKET__HPP
#define SOCKET__HPP

enum socketType
{
	SERVER = 1,
	CLIENT
};

class Socket
{
protected:
	int fd;
	socketType type;

public:
	Socket(int fd, socketType type);
	Socket(const Socket &obj);
	Socket operator=(const Socket &obj);
	~Socket();

public:
	int getFd(void);
	socketType getType(void);
};

#endif
