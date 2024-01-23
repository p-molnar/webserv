#ifndef SYSCALL__HPP
#define SYSCALL__HPP

#include "errors.hpp"

#include <string>

#include <unistd.h>

class sysCall
{
public:
	static void access(std::string path, int mode);
};

#endif
