#ifndef CGIEXECUTOR__HPP
#define CGIEXECUTOR__HPP

#include <unistd.h>
#include <sys/wait.h>

#include <string>
#include <csignal>

#include "errors.hpp"
#include "consts.hpp"
#include "tokenizer.hpp"
#include "SysCall.hpp"
#include "HttpRequest.hpp"

class CgiExecutor
{
private:
public:
	static std::string executeCgi(const t_uri_comps &uri);
	CgiExecutor();
	~CgiExecutor();
};
#endif
