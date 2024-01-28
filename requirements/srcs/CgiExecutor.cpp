#include "RequestProcessor.hpp"
#include <iostream>

std::string RequestProcessor::executeCgi(const t_uri_comps &uri)
{
	std::string raw_html;
	std::string raw_cgi_output;

	std::string www_path = "srv/";	  // retrieved from config
	std::string cgi_bin = "cgi-bin/"; // retrieved from config
	std::cout << "exec name: " << uri.executable_name << '\n';
	std::string exec_path = www_path + cgi_bin + uri.executable_name;
	std::cout << "exec_path " << exec_path << '\n';
	SysCall::access(exec_path, X_OK);

	int filedes[2];

	SysCall::pipe(filedes);

	std::vector<char *> env;
	std::string cgi_fd_env_var = "CGI_FD=" + std::to_string(filedes[1]);
	std::string path_info_env_var = "PATH_INFO=" + uri.path_info;
	std::string query_string_env_var = "QUERY_STRING=" + uri.query_str;
	env.push_back(const_cast<char *>(cgi_fd_env_var.c_str()));
	env.push_back(const_cast<char *>(path_info_env_var.c_str()));
	env.push_back(const_cast<char *>(query_string_env_var.c_str()));
	env.push_back(NULL);

	pid_t pid;
	if ((pid = fork()) == 0)
	{
		SysCall::close(filedes[0]);
		execve(exec_path.c_str(), NULL, env.data());
	}
	else
	{
		std::string raw_cgi_output;
		SysCall::close(filedes[1]);

		int status;
		if (SysCall::waitpid(pid, &status, 0) == pid)
		{
			raw_cgi_output = readFull(filedes[0]);
		}
	}
	return raw_cgi_output;
}