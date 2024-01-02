#ifndef POLLMANAGER_HPP
#define POLLMANAGER_HPP

#include <vector>
#include <poll.h>
#include <algorithm>

/*
    #define POLLIN 0x001  There is data to read.
    #define POLLPRI 0x002 There is urgent data to read.
    #define POLLOUT 0x004 Writing now will not block.
*/

class PollManager
{
private:
    int server_fd;
    std::vector<struct pollfd> pfds;

public:
    PollManager();
    ~PollManager();

public:
    void addServerFd(int fd);
    void addSocket(int fd, int events);
    void removeSocket(int fd);
    void pollRequests();
    void acceptConnection(int socket_fd);
};

#endif