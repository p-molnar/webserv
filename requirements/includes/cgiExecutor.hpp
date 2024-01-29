#ifndef CGIEXECUTOR__HPP
#define CGIEXECUTOR__HPP

#include <unistd.h>
#include <sys/wait.h>

#include <string>
#include <csignal>

#include "errors.hpp"
#include "consts.hpp"
#include "tokenizer.hpp"
#include "sysCall.hpp"
#include "httpRequest.hpp"

class cgiExecutor
{
private:
public:
	static std::string executeCgi(const t_uri_comps &uri);
	cgiExecutor();
	~cgiExecutor();
};
#endif
