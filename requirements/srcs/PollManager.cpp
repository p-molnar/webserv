#include "PollManager.hpp"
#include <string>
#include <iostream>
#include <unistd.h>
#include <sys/select.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include "errors.hpp"

PollManager::PollManager()
{
}

PollManager::~PollManager()
{
}

void PollManager::addServerFd(int fd)
{
	server_fd = fd;
	struct pollfd pfd = {server_fd, POLLIN, 0};

	pfds.push_back(pfd);
}

void PollManager::addSocket(int fd, int events)
{
	struct pollfd pfd = {fd, events, 0};
	pfds.push_back(pfd);
}

void PollManager::removeSocket(int fd)
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

void PollManager::acceptConnection(int socket_fd)
{
	struct sockaddr_storage remoteaddr;
	socklen_t addrlen = sizeof(remoteaddr);

	int client_fd = accept(socket_fd, (struct sockaddr *)&remoteaddr, &addrlen);

	if (client_fd == -1)
	{
		throw std::runtime_error("accept: " + STRERR);
	}
	else
	{
		this->addSocket(client_fd, POLLIN);
		std::cout << "new connection on fd: " << client_fd << '\n';
	}
}

void PollManager::pollRequests()
{
	char buff[1024];

	while (true)
	{
		int active_events = poll(pfds.data(), pfds.size(), 5000); // timeout to be replaced with val from config

		if (active_events < 0)
		{
			throw std::runtime_error("poll: " + STRERR);
		}

		for (int i = 0, polled_events = 0, pfds_size = pfds.size(); polled_events < active_events && i < pfds_size; i++)
		{
			if (pfds[i].revents & POLLIN)
			{
				polled_events++;
				if (pfds[i].fd == server_fd)
				{
					this->acceptConnection(server_fd);
				}
				else
				{
					std::cout << "active event on client_fd=" << pfds[i].fd << "\n";
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
							throw std::runtime_error("recv: " + STRERR);
						}
						close(pfds[i].fd);
						this->removeSocket(pfds[i].fd);
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
							close(pfds[i].fd);
							this->removeSocket(pfds[i].fd);
							throw std::runtime_error("accept: " + STRERR);
						}
					}
				}
			}
		}
	}
}