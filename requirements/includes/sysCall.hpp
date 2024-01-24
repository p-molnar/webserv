#ifndef SYSCALL__HPP
#define SYSCALL__HPP

#include "errors.hpp"

#include <string>

#include <unistd.h>

class SysCall
{
public:
	static void access(std::string path, int mode);
};

#endif
