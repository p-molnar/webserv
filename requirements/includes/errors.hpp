#ifndef ERRORS_HPP
#define ERRORS_HPP

#include <string.h>
#include <cerrno>

#define STRERR std::string(strerror(errno))

#endif