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
    int yes = 1;

    int fd = socket(PF_INET, SOCK_STREAM, 0);   // AF_INET Specifies IPv4 A
    fcntl(fd, F_SETFL, O_NONBLOCK, FD_CLOEXEC); // Set NON-Blocking
    if (fd == -1)
    {
        std::runtime_error("server socket: " + STRERR);
    }

    this->setFd(fd);
    this->setPfd((t_pollfd){fd, POLLIN, 0});

    // setting the socket options as below will prevent the app from experiencing
    // "Address already in use" errors if it is killed and restarted within a short
    // period of time.
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, (char *)&yes, sizeof(yes));
}

ServerSocket::ServerSocket(const ASocket &obj)
{
    this->setFd(obj.getFd());
}

/* Simple destructor to close the socket.
 */
ServerSocket::~ServerSocket()
{
    if (fd >= 0)
        ::close(fd);
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

    if (bind(fd, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        ::close(fd);
        throw std::runtime_error("bind port: " + STRERR);
    }
    Log::logMsg("fd " + std::to_string(fd) + " is bound to port " + std::to_string(port));
}

void ServerSocket::listenPort(int backlog)
{
    if (listen(fd, backlog) < 0)
    {
        ::close(fd);
        throw std::runtime_error("listen port: " + STRERR);
    }
    Log::logMsg("Server is listening on port 8080");
}

void ServerSocket::recvRequest() {}
void ServerSocket::sendResponse() {}

// ClientSocket ServerSocket::acceptConnection()
// {
//     struct sockaddr_in client_addr;
//     socklen_t clilen = sizeof(client_addr);

//     int newsockfd = accept(fd, (struct sockaddr *)&client_addr, &clilen);
//     if (newsockfd < 0)
//     {
//         close(fd);
//         std::string err = strerror(errno);
//         throw std::runtime_error("accept connection: " + err);
//     }
//     std::cout << "Connection accepted" << std::endl;
//     return ClientSocket(newsockfd);
// }

t_socketType ServerSocket::getType() const { return SERVER; }