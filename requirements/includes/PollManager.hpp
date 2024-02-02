#ifndef POLLMANAGER_HPP
#define POLLMANAGER_HPP

#include <map>
#include <vector>
#include <memory>

#include "Socket.hpp"
#include "ServerSocket.hpp"
#include "ClientSocket.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "Router.hpp"

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
protected:
    // Config *config;
    std::vector<t_pollfd> pfds;
    std::map<int, std::shared_ptr<Socket>> sockets;
    
public:
    PollManager();
    // PollManager(Config *config_data);
    ~PollManager();

    Router router;

    void addSocket(std::shared_ptr<Socket> socket);
    void updatePollfd();
    void HandleGETRequest(const HttpRequest& request);
    void HandlePollInEvent(std::shared_ptr<Socket> curr_socket);
    void HandlePollOutEvent(std::shared_ptr<Socket> curr_socket);

    void processHttpRequest(const HttpRequest &request, ClientSocket &client_socket);
    void removeSocket(int fd);

    void acceptConnection(int socket_fd);

    bool shouldCloseConnection(std::shared_ptr<ClientSocket> client_socket);

    void processEvents();
};

#endif