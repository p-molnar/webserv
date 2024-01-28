#ifndef REQUESTPROCESSOR__HPP
#define REQUESTPROCESSOR__HPP

#include <unistd.h>
#include <fcntl.h>

#include <string>
#include <csignal>

#include "errors.hpp"
#include "consts.hpp"
#include "string_utils.hpp"
#include "SysCall.hpp"
#include "HttpRequest.hpp"
#include "errors.hpp"

class RequestProcessor
{
public:
	static std::string executeCgi(const t_uri_comps &uri);
	static void uploadFiles(const FormData &form_data);
	static std::string listDirectoryContent(const std::string &path);
};

#endif
