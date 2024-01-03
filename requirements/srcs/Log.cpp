#include "Log.hpp"

void Log::logMsg(std::string msg)
{
	char str_repr[256];
	const char *fmt = "%Y-%m-%d %H:%M:%S";
	std::time_t now = std::time(NULL);
	std::strftime(str_repr, sizeof(str_repr), fmt, std::localtime(&now));

	std::cout << "["
			  << str_repr
			  << "]"
			  << "\t"
			  << msg
			  << '\n';
}