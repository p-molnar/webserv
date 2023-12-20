/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Config.cpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/14 14:07:34 by bprovoos      #+#    #+#                 */
/*   Updated: 2023/12/15 09:34:39 by bprovoos      ########   odam.nl         */
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

void	LocationBlock::setIndex(char* index)
{
	this->_index = index;
}

char*	LocationBlock::getRoot()
{
	return (this->_root);
}

char*	LocationBlock::getPath()
{
	return (this->_path);
}

char*	LocationBlock::getIndex()
{
	return (this->_index);
}


ServerBlock::ServerBlock()
{
	setListenIpAddress("127.0.0.1");
	setListenPort(8080);
}

ServerBlock::~ServerBlock()
{
}

void	ServerBlock::addLocation(const LocationBlock& location)
{
	this->_locations.push_back(location);
}

void	ServerBlock::setListenIpAddress(char* listenIpAddress)
{
	this->_listenIpAddress = listenIpAddress;
}

void	ServerBlock::setListenPort(int listenPort)
{
	this->_listenPort = listenPort;
}

void	ServerBlock::setServerName(char* serverName)
{
	this->_serverName = serverName;
}

char*	ServerBlock::getListenIpAddress()
{
	return (this->_listenIpAddress);
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

void		Config::setHttpBlock(HttpBlock http)
{
	this->_http = http;
}

HttpBlock	Config::getHttpBlock()
{
	return (this->_http);
}