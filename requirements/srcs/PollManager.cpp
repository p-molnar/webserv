#include "PollManager.hpp"

PollManager::PollManager()
{
}

PollManager::~PollManager()
{
}

void PollManager::addSocket(ASocket *socket)
{
	pfds.push_back(socket->getPfd());
	sockets[socket->getFd()] = socket;
}

void PollManager::removeSocket(int fd)
{
	std::vector<t_pollfd>::iterator v_it = pfds.begin();
	std::vector<t_pollfd>::iterator v_ite = pfds.end();
	while (v_it != v_ite)
	{
		if (v_it->fd == fd)
		{
			pfds.erase(v_it);
			break;
		}
		v_it++;
	}

	std::map<int, ASocket *>::iterator m_it = sockets.find(fd);
	delete m_it->second;
	sockets.erase(m_it);
}

t_pollFds PollManager::getPfds()
{
	t_pollFds pfds;
	std::map<int, ASocket *>::iterator it = sockets.begin();

	pfds.size = sockets.size();
	pfds.arr = new struct pollfd[pfds.size];

	for (int i = 0; i < pfds.size; i++)
	{
		pfds.arr[i] = it->second->getPfd();
		it++;
	}
	return pfds;
}

void PollManager::acceptConnection(int srv_fd)
{
	struct sockaddr_storage remoteaddr;
	socklen_t addrlen = sizeof(remoteaddr);

	int cli_fd = accept(srv_fd, (struct sockaddr *)&remoteaddr, &addrlen);

	if (cli_fd == -1)
	{
		throw std::runtime_error("accept: " + STRERR);
	}
	else
	{
		this->addSocket(new ClientSocket(cli_fd));
		Log::logMsg("Client accepted on fd " + std::to_string(cli_fd));
	}
}

void PollManager::pollRequests()
{
	while (true)
	{

		int active_events = poll(pfds.data(), pfds.size(), 1000);

		if (active_events < 0)
			throw std::runtime_error("poll: " + STRERR);

		std::vector<t_pollfd>::iterator it = pfds.begin();
		std::vector<t_pollfd>::iterator ite = pfds.end();
		int polled_events = 0;
		while (it != ite && polled_events < active_events)
		{
			std::vector<t_pollfd>::iterator curr_pfd = it;
			int fd = curr_pfd->fd;
			ASocket *curr_socket = sockets[fd];

			if (curr_pfd->revents & POLLIN)
			{
				polled_events++;
				if (curr_socket->getType() == SERVER)
				{
					this->acceptConnection(fd);
				}
				else
				{
					try
					{
						curr_socket->recvRequest();
						// process request
						curr_socket->sendResponse();
					}
					catch (const ClientSocket::HungUpException &e)
					{
						Log::logMsg(e.what());
					}
					catch (const std::exception &e)
					{
						close(fd);
						PollManager::removeSocket(fd);
					}
				}
			}
			it++;
		}
	}
}
