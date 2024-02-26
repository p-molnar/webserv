#include "PollManager.hpp"
#include "Log.hpp"

#define RUNNING 1

PollManager::PollManager()
{
}

PollManager::~PollManager()
{
}

void PollManager::addSocket(std::shared_ptr<Socket> socket)
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

	std::map<int, std::shared_ptr<Socket>>::iterator m_it = sockets.find(fd);
	sockets.erase(m_it);
}

void PollManager::updatePollfd()
{
	for (auto &pfd : pfds)
	{
		std::shared_ptr<Socket> socket = sockets.at(pfd.fd);

		if (std::shared_ptr<ClientSocket> clientSocket = std::dynamic_pointer_cast<ClientSocket>(socket))
		{
			if (clientSocket->getState() == ClientSocket::State::Reading && pfd.events != POLLHUP)
				pfd.events = POLLIN;
			else if (clientSocket->getState() == ClientSocket::State::Writing && pfd.events != POLLHUP)
				pfd.events = POLLOUT;
		}
	}
}

bool PollManager::shouldCloseConnection(std::shared_ptr<ClientSocket> client_socket)
{
	const auto &connectionHeader = client_socket->getResponse().getHeader("Connection");

	if (connectionHeader == "close")
		return true;
	return false;
}

void PollManager::processEvents()
{
	Log::logMsg("Server is processing events");
	while (RUNNING)
	{
		updatePollfd();
		int active_events = SysCall::poll(pfds.data(), pfds.size(), 1000);

		for (size_t i = 0, handled_events = 0; i < pfds.size() && (int)handled_events < active_events; ++i)
		{
			if (pfds[i].revents & (POLLIN | POLLOUT))
			{
				int fd = pfds[i].fd;
				std::shared_ptr<Socket> curr_socket = sockets.at(fd);
				if (pfds[i].revents & POLLIN)
				{
					Log::logMsg("POLLIN event");
					HandlePollInEvent(curr_socket);
					handled_events++;
				}
				else if (pfds[i].revents & POLLOUT)
				{
					Log::logMsg("POLLOUT event");
					HandlePollOutEvent(curr_socket);
					handled_events++;
				}
			}
			else if (pfds[i].revents & POLLHUP)
			{
				Log::logMsg("POLLHUP event");
				removeSocket(pfds[i].fd);
				handled_events++;
			}
		}
	}
}

void PollManager::HandlePollOutEvent(std::shared_ptr<Socket> curr_socket)
{
	if (std::shared_ptr<ClientSocket> client_socket = std::dynamic_pointer_cast<ClientSocket>(curr_socket))
	{
		try
		{
			router.routeRequest(client_socket->getRequest(), client_socket->getResponse());
			client_socket->sendResponse();
		}
		catch (const ClientSocket::HungUpException &e)
		{
			PollManager::removeSocket(client_socket->getFd());
		}
		catch (const std::exception &e)
		{
			client_socket->sendResponse(httpStatus::generateErrResponse(httpStatus::errnoToStatusCode(errno)));
			PollManager::removeSocket(client_socket->getFd());
			Log::logMsg(e.what());
		}
	}
}

void PollManager::HandlePollInEvent(std::shared_ptr<Socket> curr_socket)
{
	if (std::shared_ptr<ServerSocket> server_socket = std::dynamic_pointer_cast<ServerSocket>(curr_socket))
	{
		std::shared_ptr<ClientSocket> new_client = server_socket->acceptConnection();
		PollManager::addSocket(new_client);
	}
	if (std::shared_ptr<ClientSocket> client_socket = std::dynamic_pointer_cast<ClientSocket>(curr_socket))
	{
		try
		{
			client_socket->recvRequest();
		}
		catch (const ClientSocket::HungUpException &e)
		{
			PollManager::removeSocket(client_socket->getFd());
		}
		catch (const HttpRequest::InvalidMethodException &e)
		{
			client_socket->sendResponse(httpStatus::generateErrResponse(statusCode::method_not_allowed));
			PollManager::removeSocket(client_socket->getFd());
			Log::logMsg("Method not allowed");
		}
		catch (const std::exception &e)
		{
			client_socket->sendResponse(httpStatus::generateErrResponse(httpStatus::errnoToStatusCode(errno)));
			PollManager::removeSocket(client_socket->getFd());
			if (e.what()[0] != '\0')
				Log::logMsg(e.what());
		}
	}
	return;
}
