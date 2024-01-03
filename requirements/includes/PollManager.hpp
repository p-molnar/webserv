#ifndef POLLMANAGER_HPP
#define POLLMANAGER_HPP

#include <map>
#include <vector>

#include "ASocket.hpp"
#include "ServerSocket.hpp"
#include "ClientSocket.hpp"

/*
    #define POLLIN 0x001  There is data to read.
    #define POLLPRI 0x002 There is urgent data to read.
    #define POLLOUT 0x004 Writing now will not block.
*/

typedef struct s_pollFds
{
    t_pollfd *arr;
    int size;
} t_pollFds;

class PollManager
{
private:
    std::vector<t_pollfd> pfds;
    std::map<int, ASocket *> sockets;

public:
    PollManager();
    ~PollManager();

public:
    void addSocket(ASocket *socket);
    // void addServerFd(int fd);
    // void addSocket(int fd, int events);
    void removeSocket(int fd);
    void pollRequests();
    void acceptConnection(int socket_fd);
    t_pollFds getPfds();
};

#endif