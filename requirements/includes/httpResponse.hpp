/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   httpResponse.hpp                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: tklouwer <tklouwer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/17 10:22:04 by tklouwer      #+#    #+#                 */
/*   Updated: 2024/01/29 10:49:44 by tklouwer      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

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
        std::string                         _statusline; // HttpVersion + status code

        std::string                         _response;

public:
    httpResponse();
    httpResponse(const httpResponse &obj);
    httpResponse operator=(const httpResponse &obj);
    ~httpResponse();

    void setStatusLine(const std::string &statusline);
    void setBody(const std::string &body);
    void setHeaders(const std::string &key, const std::string &value);

        std::string getHeader(const std::string &header_name) const;

        std::string getStatusLine() const { return _statusline; }
        std::string generateResponse(bool includeBody);
};

#endif