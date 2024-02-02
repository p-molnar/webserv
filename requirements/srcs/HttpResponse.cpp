#include "HttpResponse.hpp"

HttpResponse HttpResponse::generateResponse2(HttpRequest &request)
{
    (void) request;
    // std::string cgi_raw_output = RequestProcessor::executeCgi(request.getUriComps());
    // std::cout << cgi_raw_output << "\n";

    // RequestProcessor::uploadFiles(request.getFormDataObj());

    // if request_type == DIRECTORY
    // {
    //     std::string path = request.getUriComps().path;
    //     // replace with config file's default directory from which the website should be served
    //     path = path == "/" ? "srv/www/" : "srv/www/" + path;

    //     std::string s = RequestProcessor::listDirectoryContent(path);
    //     std::cout << s << '\n';
    // }
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

void HttpResponse::setBody(const std::string &body)
{
    _body = body;
}

void HttpResponse::setHeaders(const std::string &key, const std::string &value)
{
    _headers[key] = value;
}

void    HttpResponse::setStatusLine(const std::string& statusline)
{
    _statusLine = statusline;
}

 void    HttpResponse::setStatusLineAndBody(const std::string& statusline, const std::string& body)
 {
    setStatusLine(statusline);
    setBody(body);
 }

std::string HttpResponse::getHeader(const std::string &headerName) const
{
    return _headers.at(headerName);
}

std::string    HttpResponse::generateResponse(bool includeBody)
{
    Log::logMsg("Response generated, ready to sent");
    std::string response;

    response += _statusLine;
    if (includeBody)
    {
        setHeaders("Content-Length", std::to_string(_body.size()));
        setHeaders("Content-Type", "text/html");
    }
    for (const auto& header : _headers) {
        response += header.first + ": " + header.second + CRLF;
    }
    response += CRLF;
    if (includeBody) {
        response += _body;
    }
    return response;
}