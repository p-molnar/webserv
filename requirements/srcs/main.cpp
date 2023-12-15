/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tklouwer <tklouwer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/06 11:31:26 by tklouwer      #+#    #+#                 */
/*   Updated: 2023/12/15 14:00:38 by tklouwer      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"
#include <iostream>
#include <vector>
#include <poll.h>

int main() 
{
    ServerSocket serverSocket;
    std::vector<ClientSocket> clientSockets;

    if (serverSocket.bindPort(8080) != EXIT_SUCCESS) {
        std::cerr << "Failed to bind to port" << std::endl;
        return 1;
    }

    if (serverSocket.listenPort(10) != EXIT_SUCCESS) {
        std::cerr << "Failed to listen on socket" << std::endl;
        return 1;
    }

    std::cout << "Server is listening on port 8080..." << std::endl;
    while (1)
    {
        ClientSocket clientSocket = serverSocket.acceptConnection();
        std::cout << "Connection accepted" << std::endl;
        clientSockets.push_back(clientSocket);
    
    }

    return 0;
}
