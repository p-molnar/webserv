/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   httpResponse.cpp                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: tklouwer <tklouwer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/17 10:53:12 by tklouwer      #+#    #+#                 */
/*   Updated: 2024/01/25 09:49:56 by tklouwer      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "httpResponse.hpp"

void    httpResponse::setBody(const std::string& body)
{
    _body = body;
    setHeaders("Content-Length", std::to_string(body.size()));
}

void    httpResponse::setHeaders(const std::string& key, const std::string& value)
{
    _headers[key] = value;
}

void    httpResponse::setStatusLine(const std::string& statusCode)
{
    _statusline = _httpVersion + " " + statusCode;
}

std::string    httpResponse::generateResponse(bool includeBody)
{
    std::string response;

    response = _statusline + CRLF;
    for (const auto& header : _headers) {
        response += header.first + ": " + header.second + CRLF;
    }
    response += CRLF;
    if (includeBody)
        response += _body;
    return response;
}