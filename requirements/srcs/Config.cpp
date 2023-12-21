#include "Config.hpp"

LocationBlock::LocationBlock() {}

LocationBlock::~LocationBlock() {}

void LocationBlock::setAllowedMethods(const std::vector<std::string>& methods) {
	_allowedMethods = methods;
}

void LocationBlock::setAutoIndex(const std::string& autoIndex) {
	_autoIndex = autoIndex;
}

void LocationBlock::setReturn(const std::string& returnPath) {
	_return = returnPath;
}

void LocationBlock::setAlias(const std::string& alias) {
	_alias = alias;
}

void LocationBlock::setRoot(const std::string& root) {
	_root = root;
}

void LocationBlock::setPath(const std::string& path) {
	_path = path;
}

void LocationBlock::setIndex(const std::string& index) {
	_index = index;
}

std::vector<std::string> LocationBlock::getAllowedMethods() const {
	return _allowedMethods;
}

std::string LocationBlock::getAutoIndex() const {
	return _autoIndex;
}

std::string LocationBlock::getReturn() const {
	return _return;
}

std::string LocationBlock::getAlias() const {
	return _alias;
}

std::string LocationBlock::getRoot() const {
	return _root;
}

std::string LocationBlock::getPath() const {
	return _path;
}

std::string LocationBlock::getIndex() const {
	return _index;
}

void LocationBlock::addLocation(const LocationBlock& location) {
	_locations.push_back(location);
}

ServerBlock::ServerBlock() : _listenPort(0), _clientMaxBodySize(0) {}

ServerBlock::~ServerBlock() {}

void ServerBlock::setErrorPage(const std::string& errorPage) {
	_errorPage = errorPage;
}

void ServerBlock::setClientMaxBodySize(int size) {
	_clientMaxBodySize = size;
}

void ServerBlock::setRoot(const std::string& root) {
	_root = root;
}

void ServerBlock::setIndex(const std::string& index) {
	_index = index;
}

void ServerBlock::setListenIpAddress(const std::string& listenIpAddress) {
	_listenIpAddress = listenIpAddress;
}

void ServerBlock::setListenPort(int listenPort) {
	_listenPort = listenPort;
}

void ServerBlock::setServerName(const std::string& serverName) {
	_serverName = serverName;
}

const std::vector<LocationBlock>& ServerBlock::getLocations() const {
	return _locations;
}

std::string ServerBlock::getErrorPage() const {
	return _errorPage;
}

int ServerBlock::getClientMaxBodySize() const {
	return _clientMaxBodySize;
}

std::string ServerBlock::getRoot() const {
	return _root;
}

std::string ServerBlock::getIndex() const {
	return _index;
}

std::string ServerBlock::getListenIpAddress() const {
	return _listenIpAddress;
}

int ServerBlock::getListenPort() const {
	return _listenPort;
}

std::string ServerBlock::getServerName() const {
	return _serverName;
}

void ServerBlock::addLocation(const LocationBlock& location) {
	_locations.push_back(location);
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

Config::~Config()
{
	closeFile();
}

void	Config::display()
{
	std::cout << "Server IP Address: " << serverBlock.getListenIpAddress() << std::endl;
	std::cout << "Server Port: " << serverBlock.getListenPort() << std::endl;
	std::cout << "Server Name: " << serverBlock.getServerName() << std::endl;

	for (const auto& location : serverBlock.getLocations())
	{
		std::cout << "\n";
		std::cout << "Location Path: " << location.getPath() << std::endl;
		std::cout << "Location Root: " << location.getRoot() << std::endl;
		std::cout << "Location Index: " << location.getIndex() << std::endl;
	}
}

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
	std::cout << "Using config file '" << _file_path << "'" << std::endl;
}

void	Config::readFile()
{
	std::string line;
	while (getline(_config_file, line))
	{
		std::istringstream lineStream(line);
		std::string key;
		lineStream >> key;

		if (key == "server")
			continue;
		else if (key == "location")
		{
			std::string path;
			lineStream >> path;
			locationStack.push(new LocationBlock());
			locationStack.top()->setPath(path);
		}
		else if (key == "}")
		{
			if (!locationStack.empty())
			{
				LocationBlock* topLocation = locationStack.top();
				locationStack.pop();
				if (locationStack.empty())
					serverBlock.addLocation(*topLocation);
				else
					locationStack.top()->addLocation(*topLocation);
				delete topLocation;
			}
		}
		else
		{
			if (locationStack.empty())
				parseServerLine(key, lineStream, serverBlock);
			else
				parseLocationLine(key, lineStream, *locationStack.top());
		}
	}
}

void	Config::parseServerLine(const std::string& key, std::istringstream& lineStream, ServerBlock& serverBlock)
{
	if (key == "listen")
	{
		int port;
		std::string ip;
		if (!(lineStream >> ip >> port))
		{
			port = std::stoi(ip);
			ip = "127.0.0.1";
		}
		serverBlock.setListenIpAddress(removeSemicolon(ip));
		serverBlock.setListenPort(port);
	}
	else if (key == "host")
	{
		std::string host;
		lineStream >> host;
		serverBlock.setListenIpAddress(removeSemicolon(host));
	}
	else if (key == "server_name")
	{
		std::string name;
		lineStream >> name;
		serverBlock.setServerName(removeSemicolon(name));
	}
}

void	Config::parseLocationLine(const std::string& key, std::istringstream& lineStream, LocationBlock& locationBlock)
{
	if (key == "root")
	{
		std::string root;
		lineStream >> root;
		locationBlock.setRoot(removeSemicolon(root));
	}
	else if (key == "index")
	{
		std::string index;
		lineStream >> index;
		locationBlock.setIndex(removeSemicolon(index));
	}
}

void	Config::closeFile()
{
	if (_config_file.is_open())
		_config_file.close();
}

void	Config::parseFile()
{
	openFile();
	readFile();
	closeFile();
}

std::string removeSemicolon(const std::string& str)
{
    if (!str.empty() && str.back() == ';')
        return str.substr(0, str.size() - 1);
    return str;
}
