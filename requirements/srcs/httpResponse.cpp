/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   httpResponse.cpp                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: tklouwer <tklouwer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/17 10:53:12 by tklouwer      #+#    #+#                 */
/*   Updated: 2024/01/19 13:27:53 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

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
    cgiExecutor::executeCgi(request.getRequestLineComp("request_uri"));
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