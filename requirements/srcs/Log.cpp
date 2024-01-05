#include "Log.hpp"

const std::string Log::getTime()
{
	char str_repr[256];
	const char *fmt = "%Y-%m-%d %H:%M:%S";
	std::time_t now = std::time(NULL);
	std::strftime(str_repr, sizeof(str_repr), fmt, std::localtime(&now));

	return std::string(str_repr);
}

void Log::logMsg(std::string msg)
{
	std::string log_time = Log::getTime();

	std::cout
		<< "["
		<< log_time
		<< "]"
		<< "\t"
		<< msg
		<< '\n';
}

void Log::logMsg(int fd, std::string msg)
{
	std::string log_time = Log::getTime();

	std::cout << "["
			  << log_time
			  << "]"
			  << "\t"
			  << "fd_"
			  << fd
			  << "  "
			  << msg
			  << '\n';
}