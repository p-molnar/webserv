/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   PollManager.hpp                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: tklouwer <tklouwer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/15 14:35:38 by tklouwer      #+#    #+#                 */
/*   Updated: 2023/12/18 09:18:05 by dickklouwer   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef POLLMANAGER_HPP
#define POLLMANAGER_HPP

#include <vector>

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

};

#endif