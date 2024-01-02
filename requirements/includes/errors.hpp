#ifndef ERRORS_HPP
#define ERRORS_HPP

#include <cerrno>
#include <string>

#define STRERR std::string(strerror(errno))

#endif