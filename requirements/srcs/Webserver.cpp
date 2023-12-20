#include "WebServer.hpp"
#include <stdexcept>
#include "ServerSocket.hpp"

WebServer::WebServer(){};

void WebServer::loadConfig(){
    // load parsed configuration file;
};

void WebServer::startService()
{
    server_socket.bindPort(8080);
    server_socket.listenPort(10);
    std::cout << "server socket: " << server_socket.getFd() << '\n';
    WebServer::addPfd(server_socket.getFd(), POLLIN);
    WebServer::pollClients();
}

void WebServer::addPfd(int fd, short events)
{
    struct pollfd pfd = {fd, events, 0};
    pfds.push_back(pfd);
}

void WebServer::removePfd(int fd)
{
    std::vector<struct pollfd>::iterator it = pfds.begin();
    std::vector<struct pollfd>::iterator ite = pfds.end();
    while (it != ite)
    {
        if (it->fd == fd)
        {
            pfds.erase(it);
            break;
        }
        it++;
    }
}

void WebServer::pollClients()
{
    int client_fd;
    char buff[1024];

    while (true)
    {
        int poll_count = poll(pfds.data(), pfds.size(), 5000); // timeout to be replaced with val from config

        if (poll_count < 0)
        {
            std::string err = strerror(errno);
            throw std::runtime_error("poll: " + err);
        }
        // std::vector<int>::iterator curr_fd = pfds.begin();
        // std::vector<int>::iterator last = pfds.end();
        for (int i = 0, pfds_size = pfds.size(); i < pfds_size; i++)
        {
            if (pfds[i].revents & POLLIN)
            {
                if (pfds[i].fd == server_socket.getFd())
                {
                    struct sockaddr_storage remoteaddr;
                    socklen_t addrlen = sizeof(remoteaddr);

                    client_fd = accept(server_socket.getFd(), (struct sockaddr *)&remoteaddr, &addrlen);

                    if (client_fd == -1)
                    {
                        throw std::runtime_error("accept: " + std::string(strerror(errno)));
                    }
                    else
                    {
                        WebServer::addPfd(client_fd, POLLIN);
                        std::cout << "new connection on fd: " << client_fd << '\n';
                    }
                }
                else
                {
                    std::cout << "event on already accepted client (" << pfds[i].fd << ") \n";
                    int bytes_received = recv(pfds[i].fd, buff, sizeof(buff), 0);
                    buff[bytes_received] = '\0';
                    std::cout << "bytes received: " << bytes_received << '\n';
                    if (bytes_received <= 0)
                    {
                        if (bytes_received == 0)
                        {
                            std::cout << "client " << pfds[i].fd << " hung up\n";
                        }
                        else
                        {
                            throw std::runtime_error("recv: " + std::string(strerror(errno)));
                        }
                        close(pfds[i].fd);
                        WebServer::removePfd(pfds[i].fd);
                    }
                    else
                    {
                        std::cout << "\nREQUEST:\n"
                                  << buff
                                  << "REQUEST END\n";
                        std::string response = "HTTP/1.1 200 OK\r\n\r\nwe got your request\n" + std::string(buff);
                        int bytes_sent = send(pfds[i].fd, response.c_str(), response.size(), 0);
                        std::cout << "bytes sent: " << bytes_sent << '\n';
                        if (bytes_sent < 0)
                        {
                            throw std::runtime_error("accept: " + std::string(strerror(errno)));
                        }
                        close(pfds[i].fd);
                        WebServer::removePfd(pfds[i].fd);
                    }
                }
            }
        }
    }
}

WebServer::~WebServer() {}