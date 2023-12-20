/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   PollManager.hpp                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: tklouwer <tklouwer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/15 14:35:38 by tklouwer      #+#    #+#                 */
/*   Updated: 2023/12/18 14:05:04 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

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
    std::vector<struct pollfd> fds;

public:
    PollManager();
    ~PollManager();

    void addFd(int fd, short events);
    void removeFd(int fd);

    std::vector<struct pollfd> getPollFds(void);
};

#endif