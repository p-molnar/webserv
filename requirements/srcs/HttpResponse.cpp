#include "HttpResponse.hpp"

void HttpResponse::setBody(const std::string &body)
{
    _body = body;
    setHeaders("Content-Length", std::to_string(body.size()));
}

void HttpResponse::setHeaders(const std::string &key, const std::string &value)
{
    _headers[key] = value;
}

void HttpResponse::setStatusCode(const std::string &statusCode)
{
    _statusCode = statusCode;
}

HttpResponse HttpResponse::generateResponse(HttpRequest &request)
{
    // std::string cgi_raw_output = RequestProcessor::executeCgi(request.getUriComps());
    // std::cout << cgi_raw_output << "\n";

    RequestProcessor::uploadFiles(request);
    return HttpResponse();
}

HttpResponse::HttpResponse(const HttpResponse &obj)
{
    (void)obj;
}

HttpResponse HttpResponse::operator=(const HttpResponse &obj)
{
    (void)obj;
    return *this;
};

HttpResponse::HttpResponse() : _httpVersion("HTTP/1.1"){};
HttpResponse::~HttpResponse() {}