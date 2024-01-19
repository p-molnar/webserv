#ifndef CGIEXECUTOR__HPP
#define CGIEXECUTOR__HPP

#include <string>
#include <unistd.h>
#include <csignal>

#include "errors.hpp"
#include "consts.hpp"
#include "tokenizer.hpp"

class cgiExecutor
{
private:
public:
	static std::string executeCgi(std::string uri);
	cgiExecutor(/* args */);
	~cgiExecutor();
};
#endif
