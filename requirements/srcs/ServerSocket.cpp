/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ServerSocket.cpp                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: tklouwer <tklouwer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/06 10:36:57 by tklouwer      #+#    #+#                 */
/*   Updated: 2023/12/18 12:33:43 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ServerSocket.hpp"

/* How It Creates a Server:
    To use this class to create a server, you would:

    Instantiate a ServerSocket object.
    Call bindPort with the desired port number.
    Call listenPort with a suitable backlog size.
    Continuously call acceptConnection in a loop to accept incoming client connections.
*/

/* Constuctor: Creates a TCP socket using socket(AF_INET, SOCK_STREAM, 0).
    - AF_INET: Specifies the IPv4 address family.
    - SOCK_STREAM: Specifies TCP Socket.
    - 0: Automatically choses the appropriate protocol.
    If socket creation fails (sockfd == -1), it prints an error message and exits.
 */
ServerSocket::ServerSocket()
{
    this->sockfd = socket(AF_INET, SOCK_STREAM, getprotobyname("tcp")->p_proto); // AF_INET Specifies IPv4 A
    fcntl(this->sockfd, F_SETFL, O_NONBLOCK);                                    // Set NON-Blocking
    if (sockfd == -1)
    {
        std::runtime_error(strerror(errno));
    }
}

/* Simple destructor to close the socket.
 */
ServerSocket::~ServerSocket()
{
    if (sockfd >= 0)
        close(sockfd);
}

/* This function binds the Socket ('sockfd') to the specified port.
    It configures the socket to listen for incoming connections on the given port.
    The function uses the 'AF_INET' address family (IPv4) and sets the address to 'INADDR_ANY',
    allowing the socket to accept connections to all IP addresses of the machine.

    - struct sockaddr_in: specifies an endpoint address to which bound / communicate.
 */
void ServerSocket::bindPort(int port)
{
    struct sockaddr_in addr;

    memset(&addr, 0, sizeof(addr));    // Initialize the struct with zeros
    addr.sin_family = AF_INET;         // Set the address family to IPv4
    addr.sin_addr.s_addr = INADDR_ANY; // Set the port number
    addr.sin_port = htons(port);       // Bind to all interfaces

    if (bind(sockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        close(sockfd);
        throw std::runtime_error(strerror(errno));
    }
}

void ServerSocket::listenPort(int backlog)
{
    (void)backlog;
    if (listen(sockfd, 10) < 0)
    {
        close(sockfd);
        throw std::runtime_error(strerror(errno));
    }
}

ClientSocket ServerSocket::acceptConnection()
{
    struct sockaddr_in client_addr;
    socklen_t clilen = sizeof(client_addr);

    int newsockfd = accept(sockfd, (struct sockaddr *)&client_addr, &clilen);
    if (newsockfd < 0)
    {
        close(sockfd);
        throw std::runtime_error(strerror(errno));
    }
    return ClientSocket(newsockfd);
}
