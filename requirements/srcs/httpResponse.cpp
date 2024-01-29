/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   httpResponse.cpp                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: tklouwer <tklouwer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/17 10:53:12 by tklouwer      #+#    #+#                 */
/*   Updated: 2024/01/29 10:12:40 by tklouwer      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "httpResponse.hpp"
#include "Log.hpp"

void    httpResponse::setBody(const std::string& body)
{
    _body = body;
}

void    httpResponse::setHeaders(const std::string& key, const std::string& value)
{
    _headers[key] = value;
}

void    httpResponse::setStatusLine(const std::string& statusline)
{
    _statusline = statusline;
}

std::string httpResponse::getHeader(const std::string &headerName) const
{
    return _headers.at(headerName);
}

std::string    httpResponse::generateResponse(bool includeBody)
{
    Log::logMsg("Response generated, ready to sent");
    std::string response;

    response += _statusline;
    if (includeBody)
    {
        setHeaders("Content-Length", std::to_string(_body.size()));
        setHeaders("Content-Type", "text/html");
    }
    for (const auto& header : _headers) {
        response += header.first + ": " + header.second + CRLF;
    }
    // setHeaders("Connection", "close"); FIX THIS ;
    response += CRLF;
    if (includeBody) {
        response += _body;
    }
    return response;
}