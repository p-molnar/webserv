#ifndef CONSTS__HPP
#define CONSTS__HPP

#include <string>

#define CRLF std::string("\r\n")		 // carriage return and new line
#define DBL_CRLF std::string("\r\n\r\n") // double carriage return and new line
#define SP std::string(" ")				 // single space separator
#define SP_ " "							 // single space (C string);
#define HEADER_SEP std::string(": ")	 // separator of an http header's key-val parseRequestLine
#define DIR_SEP std::string("/")		 // directory separator, e.g. var/www/cgi-bin
#define QSTR_SEP std::string("?")		 // query string separator
#define QPARAM_SEP std::string("&")		 // query param separator
#define QPARAM_KV_SEP std::string("=")	 // query param's key-value separator

#define NPOS std::string::npos

#endif