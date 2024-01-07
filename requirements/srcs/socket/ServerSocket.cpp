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
ServerSocket::ServerSocket(){};

void ServerSocket::createSocket()
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
    Log::logMsg("file descriptor reserved for server: " + std::to_string(fd));
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, (char *)&yes, sizeof(yes));
}

ServerSocket::ServerSocket(const Socket &obj)
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
    Log::logMsg(fd, "file descriptor is bound to port " + std::to_string(port));
}

void ServerSocket::listenPort(int backlog)
{
    if (listen(fd, backlog) < 0)
    {
        ::close(fd);
        throw std::runtime_error("listen port: " + STRERR);
    }
    Log::logMsg(fd, "server is listening on port 8080");
}

ClientSocket *ServerSocket::acceptConnection()
{
    struct sockaddr_storage remoteaddr;
    socklen_t addrlen = sizeof(remoteaddr);

    int cli_fd = accept(fd, (struct sockaddr *)&remoteaddr, &addrlen);

    if (cli_fd == -1)
    {
        throw std::runtime_error("accept: " + STRERR);
    }
    else
    {
        Log::logMsg(fd, "new connection accepted: " + std::to_string(cli_fd));
    }

    return new ClientSocket(cli_fd);
}
