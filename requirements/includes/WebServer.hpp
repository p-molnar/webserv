/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   WebServer.hpp                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tklouwer <tklouwer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/06 09:00:06 by tklouwer      #+#    #+#                 */
/*   Updated: 2023/12/18 22:36:46 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_HPP
#define WEBSERV_HPP

#include "ServerSocket.hpp"
#include "ClientSocket.hpp"
#include "PollManager.hpp"

#include <vector>
#include <map>
#include <memory>

class WebServer
{
private:
    PollManager _pollManager;
    std::map<int, std::shared_ptr<ServerSocket> > _activeServer;
    std::map<int, std::shared_ptr<ClientSocket> > _activeClients;

public:
    WebServer(){};
    ~WebServer(){};

    void addFdToPollManager(int fd, short events);
    void pollClients();
};

#endif