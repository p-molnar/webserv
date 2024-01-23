#include "sysCall.hpp"

void sysCall::access(std::string path, int mode)
{
	if (::access(path.c_str(), mode) == -1)
		throw std::runtime_error("access error: " + STRERR);
}