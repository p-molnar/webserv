/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   httpResponse.cpp                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: tklouwer <tklouwer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/17 10:53:12 by tklouwer      #+#    #+#                 */
/*   Updated: 2024/01/26 13:46:23 by tklouwer      ########   odam.nl         */
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

    response += _statusline + CRLF;
    setHeaders("Content-Type", "text/html");
    setHeaders("Connection", "close");
    response += DBL_CRLF;
    if (includeBody)
    {
        response += _body;
        setHeaders("Content-Length", std::to_string(_body.size()));
    }
    Log::logMsg(response);
    return response;
}