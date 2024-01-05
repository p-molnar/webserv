#ifndef LOG__HPP
#define LOG__HPP

#include <iostream>
#include <string>
#include <ctime>

class Log
{
private:
	static const std::string getTime();

public:
	static void logMsg(std::string msg);
	static void logMsg(int fd, std::string msg);
};

#endif
