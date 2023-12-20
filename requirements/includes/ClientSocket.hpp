/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ClientSocket.hpp                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: tklouwer <tklouwer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/06 11:53:18 by tklouwer      #+#    #+#                 */
/*   Updated: 2023/12/18 14:08:00 by tklouwer      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENTSOCKET_HPP
#define CLIENTSOCKET_HPP

// #include "WebServer.hpp"
#include <fcntl.h>
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

class ClientSocket 
{
    private:
        int     _clientfd;

    public:
        ClientSocket(int newsockfd);
        ~ClientSocket();

        int getClientFd() { return this->_clientfd; };
        ssize_t pullMessage(char *buffer, size_t length);
        ssize_t sendMessage(const char *buffer, size_t length);
        void closeFd();
};

#endif