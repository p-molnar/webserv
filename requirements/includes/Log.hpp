/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Log.hpp                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tklouwer <tklouwer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/26 12:11:31 by tklouwer      #+#    #+#                 */
/*   Updated: 2024/02/26 12:11:43 by tklouwer      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOG__HPP
#define LOG__HPP

/* C/C++ Libs */
#include <iostream>
#include <string>
#include <sys/time.h>
#include <ctime>
#include <cstdio>

/* Webserv */
#include "Config.hpp"

enum e_fd_id
{
	FD_UNDEF = -2
};

class Log
{
private:
	static const std::string getTime();
	static const std::string getMsec();

public:
	static void logMsg(std::string msg, int fd = FD_UNDEF);
};

#endif
