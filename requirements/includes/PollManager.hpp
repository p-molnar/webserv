#ifndef POLLMANAGER_HPP
#define POLLMANAGER_HPP

#include <map>
#include <vector>

#include "Socket.hpp"
#include "ServerSocket.hpp"
#include "ClientSocket.hpp"
#include "httpRequest.hpp"

/*
    #define POLLIN 0x001  There is data to read.
    #define POLLPRI 0x002 There is urgent data to read.
    #define POLLOUT 0x004 Writing now will not block.
*/

typedef struct  s_pollFds
{
    t_pollfd *arr;
    int size;
}               t_pollFds;

class PollManager
{
    private:
        std::vector<t_pollfd> pfds;
        std::map<int, Socket *> sockets;

    public:
        PollManager();
        ~PollManager();

        void addSocket(Socket *socket);
        // void addServerFd(int fd);
        // void addSocket(int fd, int events);

        void HandlePollInEvent(Socket* curr_socket);

        void processHttpRequest(const httpRequest& request, ClientSocket& client_socket);
        void removeSocket(int fd);
        void pollRequests();
        void acceptConnection(int socket_fd);
        t_pollFds getPfds();
};

#endif