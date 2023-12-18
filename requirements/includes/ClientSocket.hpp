/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ClientSocket.hpp                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: tklouwer <tklouwer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/06 11:53:18 by tklouwer      #+#    #+#                 */
/*   Updated: 2023/12/18 12:52:03 by tklouwer      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENTSOCKET_HPP
#define CLIENTSOCKET_HPP

#include "WebServer.hpp"

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