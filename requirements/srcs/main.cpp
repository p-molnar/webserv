/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tklouwer <tklouwer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/06 11:31:26 by tklouwer      #+#    #+#                 */
/*   Updated: 2023/12/06 13:50:43 by tklouwer      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"
#include <iostream>

int main() {
    ServerSocket serverSocket;

    if (serverSocket.bindPort(8080) != EXIT_SUCCESS) {
        std::cerr << "Failed to bind to port" << std::endl;
        return 1;
    }

    if (serverSocket.listenPort(10) != EXIT_SUCCESS) {
        std::cerr << "Failed to listen on socket" << std::endl;
        return 1;
    }

    std::cout << "Server is listening on port 8080..." << std::endl;

    ClientSocket clientSocket = serverSocket.acceptConnection();
    std::cout << "Connection accepted" << std::endl;

    return 0;
}
