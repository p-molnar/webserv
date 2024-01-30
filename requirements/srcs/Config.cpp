#include "Config.hpp"

Config &Config::get()
{
	if (instance == nullptr)
		instance = new Config;
	return *instance;
}

void Config::setConfig(int port)
{
	if (server_config == nullptr)
	{
		for (ServerBlock config : Config::get().getServers())
		{
			if (config.getListenPort() == port)
			{
				server_config = &config;
				break;
			}
		}
	}
}

ServerBlock &Config::getConfig()
{
	return *server_config;
}

void Config::destruct()
{
	delete instance;
	instance = nullptr;
}

LocationBlock::LocationBlock()
{
	_path = "/";
	_root = "/var/www/html";
	_index = "index.html";
	_autoIndex = "off";
	_return = "";
	_alias = "";
}

LocationBlock::~LocationBlock() {}

void LocationBlock::addAllowedMethod(const std::string &method)
{
	_allowedMethods.push_back(method);
}

void LocationBlock::setAutoIndex(const std::string &autoIndex)
{
	_autoIndex = autoIndex;
}

void LocationBlock::setReturn(const std::string &returnPath)
{
	_return = returnPath;
}

void LocationBlock::setAlias(const std::string &alias)
{
	_alias = alias;
}

void LocationBlock::setRoot(const std::string &root)
{
	_root = root;
}

void LocationBlock::setPath(const std::string &path)
{
	_path = path;
}

void LocationBlock::setIndex(const std::string &index)
{
	_index = index;
}

void LocationBlock::addCgiPath(const std::string &cgiPath)
{
	_cgiPath.push_back(cgiPath);
}

void LocationBlock::addCgiExt(const std::string &cgiExt)
{
	_cgiExt.push_back(cgiExt);
}

std::vector<std::string> LocationBlock::getAllowedMethods() const
{
	return _allowedMethods;
}

std::string LocationBlock::getAutoIndex() const
{
	return _autoIndex;
}

std::string LocationBlock::getReturn() const
{
	return _return;
}

std::string LocationBlock::getAlias() const
{
	return _alias;
}

std::vector<std::string> LocationBlock::getCgiPath() const
{
	return _cgiPath;
}

std::vector<std::string> LocationBlock::getCgiExt() const
{
	return _cgiExt;
}

std::string LocationBlock::getRoot() const
{
	return _root;
}

std::string LocationBlock::getPath() const
{
	return _path;
}

std::string LocationBlock::getIndex() const
{
	return _index;
}

void LocationBlock::addLocation(const LocationBlock &location)
{
	_locations.push_back(location);
}

ServerBlock::ServerBlock()
{
	_listenPort = 8080;
	_listenIpAddress = "127.0.0.1";
	_serverName = "localhost";
	_clientMaxBodySize = 1024;
	_index = "index.html";
	_root = "/var/www/html";
	_errorPage = "error.html";
}

ServerBlock::~ServerBlock() {}

void ServerBlock::setErrorPage(const std::string &errorPage)
{
	_errorPage = errorPage;
}

void ServerBlock::setClientMaxBodySize(int size)
{
	_clientMaxBodySize = size;
}

void ServerBlock::setRoot(const std::string &root)
{
	_root = root;
}

void ServerBlock::setIndex(const std::string &index)
{
	_index = index;
}

void ServerBlock::setListenIpAddress(const std::string &listenIpAddress)
{
	_listenIpAddress = listenIpAddress;
}

void ServerBlock::setListenPort(int listenPort)
{
	_listenPort = listenPort;
}

void ServerBlock::setServerName(const std::string &serverName)
{
	_serverName = serverName;
}

std::vector<LocationBlock> &ServerBlock::getLocations()
{
	return _locations;
}

std::string ServerBlock::getErrorPage() const
{
	return _errorPage;
}

int ServerBlock::getClientMaxBodySize() const
{
	return _clientMaxBodySize;
}

std::string ServerBlock::getRoot() const
{
	return _root;
}

std::string ServerBlock::getIndex() const
{
	return _index;
}

std::string ServerBlock::getListenIpAddress() const
{
	return _listenIpAddress;
}

int ServerBlock::getListenPort() const
{
	return _listenPort;
}

std::string ServerBlock::getServerName() const
{
	return _serverName;
}

void ServerBlock::addLocation(const LocationBlock &location)
{
	_locations.push_back(location);
}

// Config::Config() : _file_path(DEFAULT_CONFIG_PATH)
// {
// 	parseFile();
// }

void Config::parse(const char *file_path)
{
	_file_path = file_path;
	parseFile();
}

void Config::parse(int argc, char *argv[])
{
	if (argc > 1 && argv[1] != NULL)
		_file_path = argv[1];
	else
		_file_path = DEFAULT_CONFIG_PATH;
	parseFile();
}

Config::~Config()
{
	closeFile();
}

void Config::display()
{
	for (auto &server : getServers())
	{
		std::cout << "-----------------" << std::endl;
		std::cout << "Server Port: " << server.getListenPort() << std::endl;
		std::cout << "Server IP Address: " << server.getListenIpAddress() << std::endl;
		std::cout << "Server Name: " << server.getServerName() << std::endl;
		std::cout << "Server Error Page: " << server.getErrorPage() << std::endl;
		std::cout << "Server client max body size: " << server.getClientMaxBodySize() << std::endl;
		std::cout << "Server Root: " << server.getRoot() << std::endl;
		std::cout << "Server Index: " << server.getIndex() << std::endl;

		for (const auto &location : server.getLocations())
		{
			std::cout << "\n";
			std::cout << "Location path: " << location.getPath() << std::endl;
			std::cout << "Location root: " << location.getRoot() << std::endl;
			std::cout << "Location autoindex: " << location.getAutoIndex() << std::endl;
			for (const auto &method : location.getAllowedMethods())
				std::cout << "Location allowed method: " << method << std::endl;
			std::cout << "Location index: " << location.getIndex() << std::endl;
			std::cout << "Location return: " << location.getReturn() << std::endl;
			std::cout << "Location alias: " << location.getAlias() << std::endl;
			for (const auto &cgi_path : location.getCgiPath())
				std::cout << "Location cgi_path: " << cgi_path << std::endl;
			for (const auto &cgi_ext : location.getCgiExt())
				std::cout << "Location cgi_ext: " << cgi_ext << std::endl;
		}
	}
}

void Config::openFile()
{
	if (_file_path == NULL)
		_file_path = DEFAULT_CONFIG_PATH;
	_config_file.open(_file_path);
	if (!_config_file.is_open())
	{
		std::cout << "Error: Can not read file '" << _file_path << "'" << std::endl;
		exit(1);
	}
	std::cout << "Using config file '" << _file_path << "'" << std::endl;
}

void Config::readFile()
{
	int line_nr = 1;
	std::string line;
	std::string key, value;
	std::stack<std::string> block;

	while (getline(_config_file, line))
	{
		std::istringstream lineStream(line);
		while (lineStream >> key)
		{
			if (key[0] == '#')
				break;
			if (key == "server")
			{
				// std::cout << CGRN << "Block " << key << NC << std::endl;
				lineStream >> key;
				if (key == "{")
				{
					ServerBlock serverBlock;
					addServer(serverBlock);
					block.push("server");
				}
				else
					std::cout << CRED << "Error config format, line " << NC << line_nr << ": '" << line << "'" << std::endl;
			}
			else if (key == "location")
			{
				// std::cout << CGRN << "Block " << key << NC << " ";
				std::string path;
				lineStream >> path;
				// std::cout << path  << std::endl;
				lineStream >> key;
				if (key == "{")
				{
					block.push("location");
					LocationBlock locationBlock;
					getServers().back().addLocation(locationBlock);
					getServers().back().getLocations().back().setPath(path);
				}
				else
					std::cout << CRED << "Error config format, line " << NC << line_nr << ": '" << line << "'" << std::endl;
			}
			else if (key == "}")
			{
				if (!block.empty())
				{
					// std::cout << CGRN << "End Block " << block.top() << NC << std::endl;
					block.pop();
				}
				else
					std::cout << CRED << "Error config format, line " << NC << line_nr << ": '" << line << "'" << std::endl;
			}
			else if (!block.empty() && block.top() == "server")
			{
				value = "";
				while (value.back() != ';' && lineStream >> value)
				{
					// std::cout << "key = '" << key << "' value = '" << removeSemicolon(value) << "'" << std::endl;
					if (key == "listen" && is_number(removeSemicolon(value)))
						getServers().back().setListenPort(std::stoi(removeSemicolon(value)));
					if (key == "host")
						getServers().back().setListenIpAddress(removeSemicolon(value));
					if (key == "server_name")
						getServers().back().setServerName(removeSemicolon(value));
					if (key == "error_page")
						getServers().back().setErrorPage(removeSemicolon(value));
					if (key == "client_max_body_size" && is_number(removeSemicolon(value)))
						getServers().back().setClientMaxBodySize(std::stoi(removeSemicolon(value)));
					if (key == "root")
						getServers().back().setRoot(removeSemicolon(value));
					if (key == "index")
						getServers().back().setIndex(removeSemicolon(value));
				}
				// if (value == "")
				// std::cout << "key = '" << key << "' value = ''" << std::endl;
			}
			else if (!block.empty() && block.top() == "location")
			{
				value = "";
				while (value.back() != ';' && lineStream >> value)
				{
					// std::cout << "key = '" << key << "' value = '" << removeSemicolon(value) << "'" << std::endl;
					if (key == "root")
						getServers().back().getLocations().back().setRoot(removeSemicolon(value));
					if (key == "autoindex")
						getServers().back().getLocations().back().setAutoIndex(removeSemicolon(value));
					if (key == "index")
						getServers().back().getLocations().back().setIndex(removeSemicolon(value));
					if (key == "allow_methods")
						getServers().back().getLocations().back().addAllowedMethod(removeSemicolon(value));
					if (key == "return")
						getServers().back().getLocations().back().setReturn(removeSemicolon(value));
					if (key == "alias")
						getServers().back().getLocations().back().setAlias(removeSemicolon(value));
					if (key == "cgi_path")
						getServers().back().getLocations().back().addCgiPath(removeSemicolon(value));
					if (key == "cgi_ext")
						getServers().back().getLocations().back().addCgiExt(removeSemicolon(value));
				}
				// if (value == "")
				// std::cout << "key = '" << key << "' value = ''" << std::endl;
			}
			// else
			// {
			// 	value = "";
			// 	while (value.back() != ';' && lineStream >> value)
			// 	{
			// 		std::cout << "key = '" << key << "' value = '" << removeSemicolon(value) << "'" << std::endl;
			// 	}
			// 	if (value == "")
			// 		std::cout << "key = '" << key << "' value = ''" << std::endl;
			// }
		}
		line_nr++;
	}
}

void Config::addServer(const ServerBlock &server)
{
	_servers.push_back(server);
}

std::vector<ServerBlock> &Config::getServers()
{
	return _servers;
}

void Config::closeFile()
{
	if (_config_file.is_open())
		_config_file.close();
}

void Config::parseFile()
{
	openFile();
	readFile();
	closeFile();
}

bool is_number(std::string s)
{
	for (size_t i = 0; i < s.length(); i++)
	{
		if (!isdigit(s[i]))
			return false;
	}
	return true;
}

std::string removeSemicolon(const std::string &str)
{
	if (!str.empty() && str.back() == ';')
		return str.substr(0, str.size() - 1);
	return str;
}
