#ifndef ERRORS_HPP
#define ERRORS_HPP

#include <cerrno>
#include <cstring>

#define STRERR std::string(strerror(errno))

#endif