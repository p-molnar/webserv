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
    this->sockfd = socket(AF_INET, SOCK_STREAM, 0); // AF_INET Specifies IPv4 A
    fcntl(this->sockfd, F_SETFL, O_NONBLOCK); // Set NON-Blocking
    if (sockfd == -1)
    {
        std::cerr << "Failed to create socket ..." << std::endl;
        exit(EXIT_FAILURE);
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
int     ServerSocket::bindPort(int port)
{
    struct sockaddr_in addr;

    memset(&addr, 0, sizeof(addr));             // Initialize the struct with zeros
    addr.sin_family = AF_INET;                  // Set the address family to IPv4
    addr.sin_addr.s_addr= INADDR_ANY;           // Set the port number
    addr.sin_port = htons(port);                // Bind to all interfaces

    if (bind(sockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0) 
    {
        std::cerr << "Failed to bind port ..." << std::endl;
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}

int     ServerSocket::listenPort(int backlog)
{
    if (listen(sockfd, backlog) < 0) 
    {
        std::cerr << "Failed to listen on socket" << std::endl;
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}

ClientSocket  ServerSocket::acceptConnection()
{
    struct sockaddr_in client_addr;
    socklen_t clilen = sizeof(client_addr);
 
    int newsockfd = accept(sockfd, (struct sockaddr *)&client_addr, &clilen) ;
    if (newsockfd < 0)
    {
        if (errno == EAGAIN || errno == EWOULDBLOCK)
            return ClientSocket(-1);
        else 
        {
            std::cerr << "Error on accept" << std::endl;
            return ClientSocket(-1);
        }
    }
    return ClientSocket(newsockfd);
}
