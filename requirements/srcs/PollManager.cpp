#include "PollManager.hpp"

PollManager::PollManager() : fds()
{
}

PollManager::~PollManager()
{
}

void    PollManager::addFd(int fd, short events)
{
    struct pollfd pfd = {fd, events, 0};
    fds.push_back(pfd);
}

void    PollManager::removeFd(int fd)
{
    fds.erase(std::remove_if(fds.begin(), fds.end(), [fd](const pollfd &fds)
        { return (fds.fd == fd); }),
            fds.end());
}

std::vector<struct pollfd> PollManager::getPollFds(void)
{
    return this->fds;
}