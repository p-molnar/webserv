#pragma once
#ifndef CONFIG_H
#define CONFIG_H

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <stack>

#define	DEFAULT_CONFIG_PATH "../default.conf"

std::string removeSemicolon(const std::string& str);

class LocationBlock {
private:
	std::string					_path;
	std::string					_root;
	std::string					_index;
	std::vector<std::string>	_allowedMethods;
	std::string					_autoIndex;
	std::string					_return;
	std::string					_alias;
	std::vector<LocationBlock>	_locations;

public:
	LocationBlock();
	~LocationBlock();

	void setAllowedMethods(const std::vector<std::string>& methods);
	void setAutoIndex(const std::string& autoIndex);
	void setReturn(const std::string& returnPath);
	void setAlias(const std::string& alias);

	std::vector<std::string> getAllowedMethods() const;
	std::string getAutoIndex() const;
	std::string getReturn() const;
	std::string getAlias() const;

	void addLocation(const LocationBlock& location);
	void setRoot(const std::string& root);
	void setPath(const std::string& path);
	void setIndex(const std::string& index);
	std::string getRoot() const;
	std::string getPath() const;
	std::string getIndex() const;
};

class ServerBlock {
private:
	std::string					_listenIpAddress;
	int							_listenPort;
	std::string 				_serverName;
	std::vector<LocationBlock>	_locations;

	std::string					_errorPage;
	int							_clientMaxBodySize;
	std::string					_root;
	std::string					_index;

public:
	ServerBlock();
	~ServerBlock();

	void setErrorPage(const std::string& errorPage);
	void setClientMaxBodySize(int size);
	void setRoot(const std::string& root);
	void setIndex(const std::string& index);

	std::string getErrorPage() const;
	int getClientMaxBodySize() const;
	std::string getRoot() const;
	std::string getIndex() const;

	void addLocation(const LocationBlock& location);
	void setListenIpAddress(const std::string& listenIpAddress);
	void setListenPort(int listenPort);
	void setServerName(const std::string& serverName);
	std::string getListenIpAddress() const;
	int getListenPort() const;
	std::string getServerName() const;
	const std::vector<LocationBlock>& getLocations() const;
};

class Config
{
private:
	const char*		_file_path;
	std::fstream	_config_file;

	void	openFile();
	void	readFile();
	void	closeFile();
	void	parseFile();

	void	parseServerLine(const std::string& key, std::istringstream& lineStream, ServerBlock& serverBlock);
	void	parseLocationLine(const std::string& key, std::istringstream& lineStream, LocationBlock& locationBlock);

public:
	Config();
	Config(const char* file_path);
	Config(int argc, char* argv[]);
	~Config();

	void	display();

	ServerBlock					serverBlock;
	std::stack<LocationBlock*>	locationStack;
};

#endif
