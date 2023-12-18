/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ServerSocket.hpp                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: tklouwer <tklouwer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/06 09:48:15 by tklouwer      #+#    #+#                 */
/*   Updated: 2023/12/18 11:03:54 by tklouwer      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVERSOCKET_HPP
#define SERVERSOCKET_HPP

#include <sys/types.h>  // Contains definitions for a number of data types used in system calls
#include <sys/socket.h> // Main sockets header
#include <netinet/in.h> // Contains constants and structures needed for internet domain addresses
#include <unistd.h>     // Provides access to the POSIX operating system API
#include <cstring>      // For memset
#include <iostream>     // For basic I/O
#include "ClientSocket.hpp"

class ClientSocket;

class ServerSocket {
    private:
        int     sockfd;

    public:
        ServerSocket();
        ~ServerSocket();

        int     bindPort(int port);
        int     listenPort(int backlog);
        ClientSocket  acceptConnection();
        
        int getServerFd() {return this->sockfd;};

};
#endif