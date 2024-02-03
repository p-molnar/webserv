#include "Config.hpp"
#include "string_utils.hpp"

void Config::parseRedirect(std::string file_path)
{
	std::string line;

	std::ifstream file(file_path);

	if (file.is_open())
	{
		while (getline(file, line))
		{
			t_redirect redir;

			std::vector<std::string> redir_comps = tokenize(line, " ");

			if (redir_comps.size() != 3)
				throw std::runtime_error("parse error on line: '" + line + "'");

			redir.status_code = std::stoi(redir_comps[0]);

			if ((redir.status_code != 301) && (redir.status_code != 302))
				throw std::runtime_error("parse error: invalid status code");

			redir.old_path = redir_comps[1];
			redir.new_path = redir_comps[2];
			redirects.push_back(redir);
		}
		file.close();
	}
	else
		std::cout << "Unable to open '" + file_path + "'";
}

t_redirect Config::applyRedirect(std::string target_path)
{
	for (t_redirect redir : redirects)
	{
		if (redir.old_path == target_path)
			return redir;
	}
	return (t_redirect){-1, "", ""};
}