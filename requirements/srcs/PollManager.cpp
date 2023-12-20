#include "PollManager.hpp"
#include <string>

PollManager::PollManager() : pfds()
{
}

PollManager::~PollManager()
{
}

// void PollManager::removeFd(int fd)
// {
//     (void)fd;
//     fds.erase(std::remove_if(fds.begin(), fds.end(), [fd](const pollfd &fds)
//                              { return (fds.fd == fd); }),
//               fds.end());
// }

// std::vector<struct pollfd> PollManager::getPollFds(void)
// {
//     return this->pfds;
// }