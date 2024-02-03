#ifndef CONFIG_H
#define CONFIG_H

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <stack>
#include <map>

#define NC "\x1B[0m"
#define CRED "\x1B[31m"
#define CGRN "\x1B[32m"
#define DEFAULT_CONFIG_PATH "../default.conf"

typedef struct s_redirect
{
	int status_code;
	std::string old_path;
	std::string new_path;
} t_redirect;

bool is_number(std::string s);
std::string removeSemicolon(const std::string &str);

class LocationBlock
{
private:
	std::string _path;
	std::string _root;
	std::string _index;
	std::string _autoIndex;
	std::string _return;
	std::string _alias;
	std::vector<std::string> _allowedMethods;
	std::vector<std::string> _cgiPath;
	std::vector<std::string> _cgiExt;
	std::vector<LocationBlock> _locations;

public:
	LocationBlock();
	~LocationBlock();

	void setPath(const std::string &path);
	void setRoot(const std::string &root);
	void setAutoIndex(const std::string &autoIndex);
	void setIndex(const std::string &index);
	void setReturn(const std::string &returnPath);
	void setAlias(const std::string &alias);
	void addAllowedMethod(const std::string &method);
	void addCgiPath(const std::string &cgiPath);
	void addCgiExt(const std::string &cgiExt);
	void addLocation(const LocationBlock &location);

	std::string getPath() const;
	std::string getRoot() const;
	std::string getAutoIndex() const;
	std::string getIndex() const;
	std::string getReturn() const;
	std::string getAlias() const;
	std::vector<std::string> getAllowedMethods() const;
	std::vector<std::string> getCgiPath() const;
	std::vector<std::string> getCgiExt() const;
};

class ServerBlock
{
private:
	int _clientMaxBodySize;
	int _listenPort;
	std::string _listenIpAddress;
	std::string _serverName;
	std::map<int, std::string> _errorPages;
	std::string _root;
	std::string _index;
	std::map<std::string, LocationBlock> _locations;

public:
	ServerBlock();
	~ServerBlock();

	void setListenPort(int listenPort);
	void setClientMaxBodySize(int size);
	void setListenIpAddress(const std::string &listenIpAddress);
	void setServerName(const std::string &serverName);
	void setErrorPage(int errorCode, const std::string &errorPage);
	void setRoot(const std::string &root);
	void setIndex(const std::string &index);
	void addLocation(const std::string &locationPath, const LocationBlock &location);

	int getListenPort() const;
	int getClientMaxBodySize() const;
	std::string getListenIpAddress() const;
	std::string getServerName() const;
	std::string getErrorPage(int errorCode) const;
	std::map<int, std::string> getErrorPages() const;
	std::string getRoot() const;
	std::string getIndex() const;
	std::map<std::string, LocationBlock> &getLocations();
};

class Config
{
private:
	// Singleton pattern design
	Config() = default;
	~Config();
	static Config *instance;
	static ServerBlock *server_config;
	// Config(const char *file_path) = default;
	// Config(int argc, char *argv[]) = default;

private:
	const char *_file_path;
	std::fstream _config_file;
	std::vector<ServerBlock> _servers;
	std::vector<t_redirect> redirects;

	void openFile();
	void readFile();
	void closeFile();
	void parseFile();
	void addServer(const ServerBlock &server);

public:
	static Config &get();
	static void setConfig(ServerBlock *server_block);
	static ServerBlock *getConfig();
	static void setConfig(int port);

	void parse(const char *file_path);
	void parse(int argc, char *argv[]);
	void parseRedirect(std::string file_path);
	t_redirect applyRedirect(std::string target_path);

public:
	static void destruct();
	void display();
	std::vector<ServerBlock> &getServers();
};

#endif
