/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ClientSocket.hpp                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: tklouwer <tklouwer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/06 11:53:18 by tklouwer      #+#    #+#                 */
/*   Updated: 2023/12/18 08:53:05 by dickklouwer   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENTSOCKET_HPP
#define CLIENTSOCKET_HPP

#include "WebServer.hpp"

class ClientSocket 
{
    private:
        int     _serverfd;

    public:
        ClientSocket(int newsockfd);
        ~ClientSocket();

        ssize_t recv(char *buffer, size_t length)
        {
            return ::recv(_serverfd, buffer, length, 0);
        }

        ssize_t send(const char *buffer, size_t length)
        {
            return ::send(_serverfd, buffer, length, 0);
        }

        void close()
        {
            ::close(_serverfd);
        }
};

#endif