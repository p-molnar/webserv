/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Config.hpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/14 14:07:51 by bprovoos      #+#    #+#                 */
/*   Updated: 2023/12/14 16:47:25 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef CONFIG_H
#define CONFIG_H

#include <cstring>
#include <vector>

class LocationBlock
{
private:
	char*						_path;
	char*						_root;
	char*						_index;
	std::vector<LocationBlock>	_locations;

public:
	LocationBlock();
	~LocationBlock();

	void	addLocation(const LocationBlock& location);

	void	setRoot(char* root);
	void	setPath(char* path);
	void	setIndex(char* index);

	char*	getRoot();
	char*	getPath();
	char*	getIndex();
};

class ServerBlock
{
private:
	int							_listenPort;
	char*						_serverName;
	std::vector<LocationBlock>	_locations;

public:
	ServerBlock();
	~ServerBlock();

	void	addLocation(const LocationBlock& location);

	void	setListenPort(int listenPort);
	void	setServerName(char* serverName);

	int		getListenPort();
	char*	getServerName();
};

class HttpBlock
{
private:
	std::vector<ServerBlock>	_servers;

public:
	HttpBlock();
	~HttpBlock();

	void	addServer(const ServerBlock& server);
};

class Config
{
private:
	

public:
	Config();
	~Config();
};




#endif
