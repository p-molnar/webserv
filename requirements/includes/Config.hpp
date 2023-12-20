#pragma once
#ifndef CONFIG_H
#define CONFIG_H

#include <iostream>
#include <cstring>
#include <fstream>
// #include <string>
#include <vector>
#include <map>

#define	DEFAULT_CONFIG_PATH "../default.conf"

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
	char*						_listenIpAddress;
	int							_listenPort;
	char*						_serverName;
	
	std::vector<LocationBlock>	_locations;

public:
	ServerBlock();
	~ServerBlock();

	void	addLocation(const LocationBlock& location);

	void	setListenIpAddress(char* listenIpAddres);
	void	setListenPort(int listenPort);
	void	setServerName(char* serverName);

	char*	getListenIpAddress();
	int		getListenPort();
	char*	getServerName();
};

class Config
{
private:
	const char*					_file_path;
	std::ifstream				_config_file;
	std::string					_content;
	std::vector<ServerBlock>	_servers;

	void	openFile();
	void	readFile();
	void	parseFile();

public:
	Config();
	Config(const char* file_path);
	Config(int argc, char* argv[]);
	~Config();

	void	addServer(const ServerBlock& server);
};

#endif
