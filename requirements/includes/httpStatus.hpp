#ifndef HTTPSTATUS_HPP
#define HTTPSTATUS_HPP

#include <string>
#include <exception>
#include <unordered_map>
#include <stdexcept>

enum class statusCode
{
	OK = 200,
	created = 201,
	accepted = 202,
	no_content = 204,
	temp_redir = 302,
	not_modified = 304,
	bad_request = 400,
	unauthorized = 401,
	forbidden = 403,
	not_found = 404,
	method_not_allowed = 405,
	request_timeout = 408,
	length_required = 411,
	payload_too_large = 413,
	uri_too_long = 414,
	unsupported_type = 415,
	internal_server_error = 500,
	not_implemented = 501,
	bad_gateway = 502,
	service_unavailable = 503,
	gateway_timeout = 504
};

class httpStatus {

	class httpStatusException : public std::runtime_error 
	{
		public:
			httpStatusException(statusCode code) : std::runtime_error(getStatusLine(code)), _code(code) {};
			statusCode code() const {return _code;}
			const char* what() const noexcept override {
				auto it = _message.find(_code);
				if (it != _message.end())
					return it->second.c_str();
				else
					return "HTTP Status Exception";
			}
		private:
			statusCode _code;

	};
	private:

	public:
		static std::unordered_map<statusCode, std::string> _message;
		static std::string getStatusLine(statusCode code);
		static std::string generateErrResponse(statusCode code);
};

#endif