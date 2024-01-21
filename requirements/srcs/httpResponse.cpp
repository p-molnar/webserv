#include "httpResponse.hpp"

void httpResponse::setBody(const std::string &body)
{
    _body = body;
    setHeaders("Content-Length", std::to_string(body.size()));
}

void httpResponse::setHeaders(const std::string &key, const std::string &value)
{
    _headers[key] = value;
}

void httpResponse::setStatusCode(const std::string &statusCode)
{
    _statusCode = statusCode;
}

httpResponse httpResponse::generateResponse(httpRequest &request)
{
    std::string cgi_raw_output = cgiExecutor::executeCgi(request.getRequestLineComp("request_uri"));
    std::cout << cgi_raw_output << "\n";
    return httpResponse();
}

httpResponse::httpResponse(const httpResponse &obj)
{
    (void)obj;
}

httpResponse httpResponse::operator=(const httpResponse &obj)
{
    (void)obj;
    return *this;
};

httpResponse::httpResponse() : _httpVersion("HTTP/1.1"){};
httpResponse::~httpResponse() {}