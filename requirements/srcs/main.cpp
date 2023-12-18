/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tklouwer <tklouwer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/06 11:31:26 by tklouwer      #+#    #+#                 */
/*   Updated: 2023/12/18 09:38:59 by dickklouwer   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/WebServer.hpp"
#include <iostream>
#include <vector>
#include <poll.h>
#include <sys/socket.h>

int main() 
{
    ServerSocket serverSocket;
    WebServer server;

    if (serverSocket.bindPort(8080) != EXIT_SUCCESS) {
        std::cerr << "Failed to bind to port" << std::endl;
        return 1;
    }

    if (serverSocket.listenPort(10) != EXIT_SUCCESS) {
        std::cerr << "Failed to listen on socket" << std::endl;
        return 1;
    }

    std::cout << "Server is listening on port 8080..." << std::endl;
    return 0;
}
