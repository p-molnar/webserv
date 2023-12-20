#include "WebServer.hpp"
#include <stdexcept>
#include "ServerSocket.hpp"

void    WebServer::addFdToPollManager(int fd, short events)
{
    _pollManager.addFd(fd, events);
}

// void    WebServer::pollClients() 
// {
//     auto fds = _pollManager.getPollFds();
//     if (poll(fds.data(), fds.size(), -1) < 0)
//     {
//         throw std::runtime_error("poll() failed:" + std::string(strerror(errno)));
//     }
//     for (auto& pfd : fds)
//     {
//         if (pfd.revents & POLLIN)
//         {
//             if (pfd.fd == 8080)
//             {
//                // addFdToPollManager(serverSocket.acceptconnection(), POLLIN); // << NEED TO WORK ON ACCEPTING AND ADDING TO INCOMING CLIENTS TO VECTOR
//             }
//         }
//     }
// }