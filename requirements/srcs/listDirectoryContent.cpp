#include "RequestProcessor.hpp"

std::string RequestProcessor::listDirectoryContent(const std::string &path)
{
	DIR *dir = SysCall::opendir(path);
	std::vector<struct dirent *> dirent_list = SysCall::listdir(dir);
	std::string dirlist;

	for (struct dirent *dir : dirent_list)
	{
		dirlist += "<a href=\"" + path + dir->d_name + "\">" + std::string(dir->d_name) + "</a>" + "<br>";
	}

	return dirlist;
}