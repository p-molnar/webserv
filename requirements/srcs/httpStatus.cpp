/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   httpStatus.cpp                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: tklouwer <tklouwer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/25 09:13:36 by tklouwer      #+#    #+#                 */
/*   Updated: 2024/02/05 13:32:52 by tklouwer      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "httpStatus.hpp"
#include "consts.hpp"
#include <iostream>

std::unordered_map<statusCode, std::string> httpStatus::_message = {
	{statusCode::OK, "OK"},
	{statusCode::Created, "Created"},
	{statusCode::Accepted, "Accepted"},
	{statusCode::NoContent, "No Content"},
	{statusCode::Found, "Found"},
	{statusCode::NotModified, "Not Modified"},
	{statusCode::BadRequest, "Bad Request"},
	{statusCode::UnAuthorized, "Unauthorized"},
	{statusCode::Forbidden, "Forbidden"},
	{statusCode::NotFound, "Not Found"},
	{statusCode::MethodNotAllowed, "Method Not Allowed"},
	{statusCode::RequestTimeout, "Request Timeout"},
	{statusCode::LengthRequired, "Length Required"},
	{statusCode::PayloadToLarge, "Payload Too Large"},
	{statusCode::URIToLong, "URI Too Long"},
	{statusCode::UnsupportedMediaType, "Unsupported Media Type"},
	{statusCode::InternalServerError, "Internal Server Error"},
	{statusCode::NotImplemented, "Not Implemented"},
	{statusCode::BadGateway, "Bad Gateway"},
	{statusCode::ServiceUnavailable, "Service Unavailable"},
	{statusCode::GatewayTimeout, "Gateway Timeout"}
};

std::string httpStatus::getStatusLine(statusCode code)
{
	return (version + " " + std::to_string(static_cast<int>(code)) + 
		" " + _message.at(code)) + CRLF;
}

static std::string generateErrResponse(statusCode code) 
{
	std::string response = httpStatus::getStatusLine(code);

	const auto& message = httpStatus::_message.at(code);
	
	std::string body = "<html><head><title>" + message + 
		"</title></head><body><h1>" + message + "</h1></body></html>";
	response += "Content-Type: text/html\r\n";
    response += "Content-Length: " + std::to_string(body.length()) + "\r\n";
    response += "Connection: close\r\n\r\n";

	response += body;
	return response;
}