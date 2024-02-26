/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   PollManager.cpp                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: tklouwer <tklouwer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/26 12:16:44 by tklouwer      #+#    #+#                 */
/*   Updated: 2024/02/26 15:40:12 by tklouwer      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "PollManager.hpp"

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
	Log::logMsg("connection removed: " + std::to_string(fd));
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

void PollManager::SendSafeResponse(std::shared_ptr<ClientSocket> clientSocket) 
{
    try {
        clientSocket->sendResponse();
    } catch (const std::exception &e) {
        Log::logMsg(e.what());
        removeSocket(clientSocket->getFd());
    }
}

void PollManager::handleEvent(int fd, short revents) 
{
    auto socket = sockets.at(fd);
    if (revents & (POLLIN | POLLHUP))
        HandlePollInEvent(socket);
    else if (revents & (POLLOUT | POLLHUP))
        HandlePollOutEvent(socket);
}

void PollManager::processEvents()
{
    Log::logMsg("Server is processing events");
    while (RUNNING) 
	{
        updatePollfd();
        int active_events = SysCall::poll(pfds.data(), pfds.size(), 1000);
		for (size_t i = 0; i < pfds.size() && active_events > 0; ++i) 
		{
			handleEvent(pfds[i].fd, pfds[i].revents);
		}
    }
}

void PollManager::sendErrorResponse(std::shared_ptr<ClientSocket> clientSocket, statusCode errorCode, const std::string& logMessage)
{
    clientSocket->sendResponse(httpStatus::generateErrResponse(errorCode));
    if (!logMessage.empty()) {
        Log::logMsg(logMessage);
	}
	removeSocket(clientSocket->getFd());
}

void PollManager::HandlePollInEvent(std::shared_ptr<Socket> currSocket) 
{
    if (auto serverSocket = std::dynamic_pointer_cast<ServerSocket>(currSocket)) 
	{
        auto newClient = serverSocket->acceptConnection();
        addSocket(newClient);
    } 
	else if (auto clientSocket = std::dynamic_pointer_cast<ClientSocket>(currSocket)) 
        handleClientSocketEvent(clientSocket, true);
}

void PollManager::HandlePollOutEvent(std::shared_ptr<Socket> currSocket) 
{
    auto clientSocket = std::dynamic_pointer_cast<ClientSocket>(currSocket);
    if (clientSocket) 
	{
        handleClientSocketEvent(clientSocket, false);
    }
}

void PollManager::handleClientSocketEvent(std::shared_ptr<ClientSocket> clientSocket, bool isPollIn) 
{
	
    try {
        if (isPollIn) {
            clientSocket->recvRequest();
        } 
		else {
            router.routeRequest(clientSocket->getRequest(), clientSocket->getResponse());
            clientSocket->sendResponse();
        }
    } 
	catch (const ClientSocket::HungUpException& e) {
        sendErrorResponse(clientSocket, httpStatus::errnoToStatusCode(errno), "Connection hung up");
    } catch (const HttpRequest::invalidRequest& e) {
        sendErrorResponse(clientSocket, statusCode::bad_request, e.what());
    } catch (const std::runtime_error& e) {
        sendErrorResponse(clientSocket, httpStatus::errnoToStatusCode(ENOSYS), e.what());
    } catch (const std::exception& e) {
        sendErrorResponse(clientSocket, httpStatus::errnoToStatusCode(errno), e.what());
    }
}
