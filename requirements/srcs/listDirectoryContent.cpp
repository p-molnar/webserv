#include "RequestProcessor.hpp"
#include <fstream>

std::string RequestProcessor::listDirectoryContent(const t_uri_comps &uri)
{
	std::string rootdir = uri.path;
	DIR *dir = SysCall::opendir(rootdir.c_str());
	std::vector<struct dirent *> dirent_list = SysCall::listdir(dir);
	std::string dirlist;


	for (struct dirent *dir : dirent_list)
	{
		std::string dirname = dir->d_name;
		dirlist += "<a href=\"" + dirname + "\">" + dirname + "</a>" + "<br>\n";
	}
	return dirlist;
}