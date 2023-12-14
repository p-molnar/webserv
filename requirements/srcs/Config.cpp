/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Config.cpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/14 14:07:34 by bprovoos      #+#    #+#                 */
/*   Updated: 2023/12/14 16:29:04 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Config.hpp"

LocationBlock::LocationBlock()
{
}

LocationBlock::~LocationBlock()
{
}

void	LocationBlock::setRoot(char* root)
{
	this->_root = root;
}

void	LocationBlock::setPath(char* path)
{
	this->_path = path;
}

char*	LocationBlock::getRoot()
{
	return (this->_root);
}

char*	LocationBlock::getPath()
{
	return (this->_path);
}

ServerBlock::ServerBlock()
{
}

ServerBlock::~ServerBlock()
{
}

void	ServerBlock::addLocation(const LocationBlock& location)
{
	this->_locations.push_back(location);
}

void	ServerBlock::setListenPort(int listenPort)
{
	this->_listenPort = listenPort;
}

void	ServerBlock::setServerName(char* serverName)
{
	this->_serverName = serverName;
}

int		ServerBlock::getListenPort()
{
	return (this->_listenPort);
}

char*	ServerBlock::getServerName()
{
	return (this->_serverName);
}

HttpBlock::HttpBlock()
{
	LocationBlock	location;
	ServerBlock		server;
	char*			str = nullptr;
	
	location.setPath(str);
	location.setRoot(str);
	server.addLocation(location);
	server.setListenPort(8080);
	server.setServerName(str);
	addServer(server);
}

HttpBlock::~HttpBlock()
{
}

void	HttpBlock::addServer(const ServerBlock& server)
{
	this->_servers.push_back(server);
}

Config::Config()
{
}

Config::~Config()
{
}
