/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   listDirectoryContent.cpp                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tklouwer <tklouwer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/26 12:15:48 by tklouwer      #+#    #+#                 */
/*   Updated: 2024/02/26 12:15:54 by tklouwer      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "RequestProcessor.hpp"

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