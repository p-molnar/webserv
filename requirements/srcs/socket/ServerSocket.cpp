#include "ServerSocket.hpp"
ServerSocket::ServerSocket(){};

void ServerSocket::createSocket()
{
    int yes = 1;

    int fd = SysCall::socket(PF_INET, SOCK_STREAM, 0);
    SysCall::fcntl(fd, F_SETFL, O_NONBLOCK, FD_CLOEXEC);

    this->setFd(fd);
    this->setPfd((t_pollfd){fd, POLLIN, 0});

    Log::logMsg("file descriptor reserved for server: " + std::to_string(fd));
    SysCall::setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, (char *)&yes, sizeof(yes));
}

ServerSocket::ServerSocket(const Socket &obj)
{
    this->setFd(obj.getFd());
}

ServerSocket::~ServerSocket()
{
    if (fd >= 0)
        ::close(fd);
}

void ServerSocket::bindPort(int port)
{
    struct sockaddr_in addr;

    memset(&addr, 0, sizeof(addr));    // Initialize the struct with zeros
    addr.sin_family = AF_INET;         // Set the address family to IPv4
    addr.sin_addr.s_addr = INADDR_ANY; // Set the port number
    addr.sin_port = htons(port);       // Bind to all interfaces

    SysCall::bind(fd, (struct sockaddr *)&addr, sizeof(addr));
    Log::logMsg("file descriptor is bound to port " + std::to_string(port), fd);
}

void ServerSocket::listenPort(int backlog)
{
    SysCall::listen(fd, backlog);
    Log::logMsg("server is listening on port 8080", fd);
}

ClientSocket *ServerSocket::acceptConnection()
{
    struct sockaddr_storage remoteaddr;
    socklen_t addrlen = sizeof(remoteaddr);

    int cli_fd = SysCall::accept(fd, (struct sockaddr *)&remoteaddr, &addrlen);

    Log::logMsg("new connection accepted: " + std::to_string(cli_fd), fd);

    return new ClientSocket(cli_fd);
}
