#ifndef HTTPSTATUS_HPP
#define HTTPSTATUS_HPP

#include <string>
#include <unordered_map>

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
	private:
		statusCode _statusCode;
		static std::unordered_map<statusCode, std::string> _message;

	public:
		httpStatus(statusCode statuscode) : _statusCode(statuscode) {};
		~httpStatus() {};

		std::string getStatusLine() const;
};

#endif