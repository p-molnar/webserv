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
    std::vector<struct pollfd> pfds;

public:
    PollManager();
    ~PollManager();

    void startService();

    // void addFd(int fd, short events);
    // void removeFd(int fd);

    // std::vector<struct pollfd> getPollFds(void);
};

#endif