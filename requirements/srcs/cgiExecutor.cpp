#include "cgiExecutor.hpp"
#include <iostream>

cgiExecutor::cgiExecutor(/* args */)
{
}

cgiExecutor::~cgiExecutor()
{
}

std::string cgiExecutor::executeCgi(std::string uri)
{
	std::string raw_html;

	std::vector<std::string> uri_comps = tokenize(uri, QSTR_SEP);

	if (uri_comps.size() != 2)
		throw std::runtime_error("No query parameters found in '" + uri + "'");

	std::string cgi_exec_name = uri_comps[0];
	std::string query_string = uri_comps[1];

	std::string www_path = "srv/";	 // retrieved from config
	std::string cgi_bin = "cgi-bin"; // retrieved from config

	std::string exec_path = www_path + cgi_bin + cgi_exec_name;
	std::cout << exec_path;
	if (access(exec_path.c_str(), X_OK))
		throw std::runtime_error("access error: " + STRERR);

	std::vector<char *> env;
	env.push_back(const_cast<char *>(query_string.c_str()));

	int filedes[2];

	if (pipe(filedes) < 0)
		throw std::runtime_error("pipe error: " + STRERR);

	std::string cgi_fd_env_var = "CGI_FD=" + std::to_string(filedes[1]);
	env.push_back(const_cast<char *>(cgi_fd_env_var.c_str()));

	char output_buff[1024];
	std::string raw_cgi_output;

	int pid = fork();
	if (pid < 0)
		throw std::runtime_error("fork error: " + STRERR);
	if (pid == 0)
	{
		if (execve(exec_path.c_str(), NULL, env.data()) < 0)
		{
			kill(pid, SIGKILL);
			throw std::runtime_error("execve error: " + STRERR);
		}

		while (int bytes_read = read(filedes[0], output_buff, sizeof(output_buff) - 1))
		{
			if (bytes_read < 0)
			{
				kill(pid, SIGKILL);
				throw std::runtime_error("execve error: " + STRERR);
			}
			output_buff[bytes_read] = '\0';
			raw_cgi_output += output_buff;
		}
	}
	kill(pid, SIGKILL);

	std::cout << raw_cgi_output;

	return "a";
}