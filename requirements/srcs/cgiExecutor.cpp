#include "CgiExecutor.hpp"
#include <iostream>

CgiExecutor::CgiExecutor(/* args */)
{
}

CgiExecutor::~CgiExecutor()
{
}

std::string CgiExecutor::executeCgi(const t_uri_comps &uri)
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

	if (pipe(filedes) < 0)
		throw std::runtime_error("pipe error: " + STRERR);

	std::vector<char *> env;
	std::string cgi_fd_env_var = "CGI_FD=" + std::to_string(filedes[1]);
	std::string path_info_env_var = "PATH_INFO=" + uri.path_info;
	std::string query_string_env_var = "QUERY_STRING=" + uri.query_str;
	env.push_back(const_cast<char *>(cgi_fd_env_var.c_str()));
	env.push_back(const_cast<char *>(path_info_env_var.c_str()));
	env.push_back(const_cast<char *>(query_string_env_var.c_str()));
	env.push_back(NULL);

	pid_t pid;
	if ((pid = fork()) < 0)
		throw std::runtime_error("fork error: " + STRERR);
	if (pid == 0)
	{
		close(filedes[0]);
		if (execve(exec_path.c_str(), NULL, env.data()) < 0)
			throw std::runtime_error("execve error: " + STRERR);
	}
	else
	{
		close(filedes[1]);
		int status;
		if (waitpid(pid, &status, 0) == pid)
		{
			char cgi_output_buff[1024];
			while (1)
			{
				int bytes_read = read(filedes[0], cgi_output_buff, sizeof(cgi_output_buff) - 1);
				if (bytes_read <= 0)
				{
					close(filedes[0]);
					if (bytes_read == 0)
						break;
					else if (bytes_read < 0)
						throw std::runtime_error("read error: " + STRERR);
				}
				std::cout << bytes_read << '\n';
				cgi_output_buff[bytes_read] = '\0';
				raw_cgi_output += cgi_output_buff;
			}
		}
	}
	return raw_cgi_output;
}