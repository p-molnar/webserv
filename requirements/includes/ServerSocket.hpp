/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ServerSocket.hpp                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: tklouwer <tklouwer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/06 09:48:15 by tklouwer      #+#    #+#                 */
/*   Updated: 2023/12/18 10:44:06 by pmolnar       ########   odam.nl         */
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
#include <stdexcept>    // For error handling, and to throw exceptions
#include <cerrno>       // Defines a set of string errors
#include "ClientSocket.hpp"

class ClientSocket;

class ServerSocket
{
private:
    int sockfd;

public:
    ServerSocket();
    ~ServerSocket();

    void bindPort(int port);
    void listenPort(int backlog);
    ClientSocket acceptConnection();
};

#endif