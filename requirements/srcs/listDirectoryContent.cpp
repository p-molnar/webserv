#include "RequestProcessor.hpp"
#include <fstream>

std::string RequestProcessor::listDirectoryContent(const std::string &path)
{
	DIR *dir = SysCall::opendir(path);
	std::vector<struct dirent *> dirent_list = SysCall::listdir(dir);
	std::string dirlist;
	std::string rootdir = "srv/www";

	for (struct dirent *dir : dirent_list)
	{
		std::string webpath = path.substr(rootdir.length()) + "/" + std::string(dir->d_name);
		if (webpath[0] != '/')
			webpath = "/" + webpath;
		dirlist += "<a href=\"" + webpath + "\">" + std::string(dir->d_name) + "</a>" + "<br>";
	}
	return dirlist;
}