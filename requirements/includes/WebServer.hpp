/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   WebServer.hpp                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tklouwer <tklouwer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/06 09:00:06 by tklouwer      #+#    #+#                 */
/*   Updated: 2023/12/18 13:18:58 by tklouwer      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_HPP
#define WEBSERV_HPP

#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/select.h>
#include "ServerSocket.hpp"
#include "ClientSocket.hpp"
#include <vector>
#include "PollManager.hpp"

class WebServer 
{
    private:
        PollManager _pollManager;

    public:
        WebServer() {};
        ~WebServer() {} ;

        void    addFdToPollManager(int fd, short events);
        void    pollClients();
};

#endif