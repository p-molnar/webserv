#ifndef HTTPSTATUS_HPP
#define HTTPSTATUS_HPP

#include <string>
#include <exception>
#include <unordered_map>
#include <stdexcept>

enum class statusCode
{
	OK = 200,
	Created = 201,
	Accepted = 202,
	NoContent = 204,
	Found = 302,
	NotModified = 304,
	BadRequest = 400,
	UnAuthorized = 401,
	Forbidden = 403,
	NotFound = 404,
	MethodNotAllowed = 405,
	RequestTimeout = 408,
	LengthRequired = 411,
	PayloadToLarge = 413,
	URIToLong = 414,
	UnsupportedMediaType = 415,
	InternalServerError = 500,
	NotImplemented = 501,
	BadGateway = 502,
	ServiceUnavailable = 503,
	GatewayTimeout = 504
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