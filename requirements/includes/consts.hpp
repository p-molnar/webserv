#ifndef CONSTS__HPP
#define CONSTS__HPP

#define CRLF std::string("\r\n")		 // carriage return and new line
#define DBL_CRLF std::string("\r\n\r\n") // double carriage return and new line
#define SP std::string(" ")				 // single space separator
#define SP_ " "							 // single space (C string);
#define HEADER_SEP ": "					 // separator of an http header's key-val pair
#define QSTR_SEP std::string("?")		 // query parameter separator
#define QPARAM_SEP std::string("&")		 // query string separator

#endif