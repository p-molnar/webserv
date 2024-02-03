#include "RequestProcessor.hpp"

std::string RequestProcessor::executeCgi(const t_uri_comps &uri)
{
	std::string raw_html;
	std::string raw_cgi_output;

	std::string cgi_root = Config::getConfig().getLocations().at("/cgi-bin").getRoot();
	std::string exec_path = cgi_root + uri.executable_name;
	SysCall::access(exec_path, X_OK);

	int filedes[2];

	SysCall::pipe(filedes);

	std::vector<char *> cgi_env;
	std::string path_info_env_var = "PATH_INFO=" + uri.path_info;
	std::string query_string_env_var = "QUERY_STRING=" + uri.query_str;
	cgi_env.push_back(const_cast<char *>(path_info_env_var.c_str()));
	cgi_env.push_back(const_cast<char *>(query_string_env_var.c_str()));
	cgi_env.push_back(NULL);

	pid_t child_pid;
	if ((child_pid = SysCall::fork()) == 0)
	{
		SysCall::dup2(filedes[1], STDOUT_FILENO);
		SysCall::close(filedes[0]);
		SysCall::execve(exec_path.c_str(), NULL, cgi_env.data());
	}
	else
	{
		SysCall::close(filedes[1]);

		int status;
		if (SysCall::waitpid(child_pid, &status, 0) > 0)
		{
			if (!WIFEXITED(status))
				throw std::runtime_error("execve error: " + std::to_string(WEXITSTATUS(status)));
		}
		raw_cgi_output = readFull(filedes[0]);
		SysCall::close(filedes[0]);
	}
	return raw_cgi_output;
}