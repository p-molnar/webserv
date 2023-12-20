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

Config::Config(): _file_path(DEFAULT_CONFIG_PATH)
{
	this->parseFile();
}

Config::Config(const char* file_path): _file_path(file_path)
{
	this->parseFile();
}

Config::Config(int argc, char* argv[])
{
	if (argc > 1 && argv[1] != NULL)
		_file_path = argv[1];
	else
		_file_path = DEFAULT_CONFIG_PATH;
	parseFile();
}

Config::~Config() {}

void	Config::openFile()
{
	if (_file_path == NULL)
		_file_path = DEFAULT_CONFIG_PATH;
	_config_file.open(_file_path);
	if (!_config_file.is_open())
	{
		std::cout << "Error: Can not read file '" << _file_path << "'" << std::endl;
		exit(1);
	}
}

void	Config::readFile()
{

}

void	Config::parseFile()
{
	openFile();
	readFile();
}
