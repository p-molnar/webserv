#ifndef HTTPRESPONSE__HPP
#define HTTPRESPONSE__HPP

#include "iostream"
#include <map>

#include "httpRequest.hpp"
#include "cgiExecutor.hpp"

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
class httpResponse
{
private:
    std::string _httpVersion;
    std::string _statusCode;
    std::string _body;
    std::map<std::string, std::string> _headers;

public:
    httpResponse();
    httpResponse(const httpResponse &obj);
    httpResponse operator=(const httpResponse &obj);
    ~httpResponse();

    void setStatusCode(const std::string &code);
    void setBody(const std::string &body);
    void setHeaders(const std::string &key, const std::string &value);

    static httpResponse generateResponse(httpRequest &request);
};

#endif