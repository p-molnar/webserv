#ifndef HTTPRESPONSE__HPP
#define HTTPRESPONSE__HPP

#include "iostream"
#include <map>

#include "HttpRequest.hpp"
#include "RequestProcessor.hpp"
#include "Log.hpp"

/*  HTTP Response
    -   HTTP VERSION    "HTTP/1.1"
    -   Status Code     "200 OK"
    -   Headers
            Key-Value pairs:
                "Content-Type"
                "Content-Length"
                "Connection"
    -   Response Body   content being returned

 */
class HttpResponse
{
private:
    std::string _httpVersion;
    std::string _statusLine;
    std::string _body;
    std::map<std::string, std::string> _headers;

public:
    HttpResponse();
    HttpResponse(const HttpResponse &obj);
    HttpResponse operator=(const HttpResponse &obj);
    ~HttpResponse();

    void    setStatusLine(const std::string& statusline);
    void setBody(const std::string &body);
    void setHeaders(const std::string &key, const std::string &value);

    std::string getHeader(const std::string &headerName) const;

    static HttpResponse generateResponse2(HttpRequest &request);
    std::string    generateResponse(bool includeBody);
};

#endif