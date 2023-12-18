/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tklouwer <tklouwer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/06 11:31:26 by tklouwer      #+#    #+#                 */
/*   Updated: 2023/12/18 10:38:53 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"
#include <iostream>

int main()
{
    try
    {
        ServerSocket serverSocket;

        serverSocket.bindPort(8080);
        serverSocket.listenPort(10);
        std::cout << "Server is listening on port 8080..." << std::endl;
        ClientSocket clientSocket = serverSocket.acceptConnection();
        std::cout << "Connection accepted" << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
