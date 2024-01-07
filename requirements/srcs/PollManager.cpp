#include "PollManager.hpp"

PollManager::PollManager()
{
}

PollManager::~PollManager()
{
}

void PollManager::addSocket(Socket *socket)
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

	std::map<int, Socket *>::iterator m_it = sockets.find(fd);
	delete m_it->second;
	sockets.erase(m_it);
}

t_pollFds PollManager::getPfds()
{
	t_pollFds pfds;
	std::map<int, Socket *>::iterator it = sockets.begin();

	pfds.size = sockets.size();
	pfds.arr = new struct pollfd[pfds.size];

	for (int i = 0; i < pfds.size; i++)
	{
		pfds.arr[i] = it->second->getPfd();
		it++;
	}
	return pfds;
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
			Socket *curr_socket = sockets[fd];

			if (curr_pfd->revents & POLLIN)
			{
				polled_events++;
				if (ServerSocket *server_socket = dynamic_cast<ServerSocket *>(curr_socket))
				{
					ClientSocket *new_client = server_socket->acceptConnection();
					PollManager::addSocket(new_client);
				}
				if (ClientSocket *client_socket = dynamic_cast<ClientSocket *>(curr_socket))
				{
					try
					{
						client_socket->recvRequest();
						// process request
						client_socket->sendResponse();
					}
					catch (const ClientSocket::HungUpException &e)
					{
						PollManager::removeSocket(client_socket->getFd());
					}
					catch (const std::exception &e)
					{
						PollManager::removeSocket(client_socket->getFd());
						Log::logMsg(e.what());
					}
				}
			}
			it++;
		}
	}
}
