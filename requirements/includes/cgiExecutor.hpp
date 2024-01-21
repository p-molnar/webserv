#ifndef CGIEXECUTOR__HPP
#define CGIEXECUTOR__HPP

#include <unistd.h>
#include <sys/wait.h>

#include <string>
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
