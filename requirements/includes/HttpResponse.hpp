/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   HttpResponse.hpp                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: tklouwer <tklouwer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/26 12:11:09 by tklouwer      #+#    #+#                 */
/*   Updated: 2024/02/26 12:11:23 by tklouwer      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPRESPONSE__HPP
#define HTTPRESPONSE__HPP

/* C/C++ Libs */
#include "iostream"
#include <map>

/* Webserv */
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
    HttpResponse(const HttpRequest& request);
    HttpResponse operator=(const HttpResponse &obj);
    ~HttpResponse();

    void setStatusLine(const std::string& statusline);
    void setBody(const std::string &body);
    void setHeaders(const std::string &key, const std::string &value);
    void setStatusLineAndBody(const std::string& statusline, const std::string& body);
    std::string getHeader(const std::string &headerName) const;

    static HttpResponse generateResponse2(HttpRequest &request);
    std::string    generateResponse(HttpRequest &request);

};

#endif