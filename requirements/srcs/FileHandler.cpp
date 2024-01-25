/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   FileHandler.cpp                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: tklouwer <tklouwer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/25 08:25:07 by tklouwer      #+#    #+#                 */
/*   Updated: 2024/01/25 14:22:11 by tklouwer      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "FileHandler.hpp"
#include "httpStatus.hpp"
#include <fstream>
#include <sstream>

bool fileHandler::fileExists(std::string& filePath)
{
    std::ifstream fileStream(filePath);
    return fileStream.good();
}

std::string fileHandler::readFileContent(const std::string& filePath)
{
    std::ifstream fileStream(filePath);
    std::stringstream buffer;

    buffer << fileStream.rdbuf();

    return buffer.str();
}

void     handleGetRequest(const httpRequest *req, httpResponse *res) 
{
    std::cout << "GET REQUEST\n";
    std::string uri = req->getHeader("request_uri");
    if (uri.empty() || uri == "/")
        uri = "/index.html";
    
    std::string filePath = "../www" + uri;
    if (fileHandler::fileExists(filePath))
    {
        std::string content = fileHandler::readFileContent(filePath);
        httpStatus status(statusCode::OK);
        res->setBody(content);
        res->setStatusLine(status.getStatusLine());
        const auto& headers = req->getHeaders();
        for (const auto& header : headers)
        {
            res->setHeaders(header.first, header.second);
        }
        res->setHeaders("Content-Length", std::to_string(content.size()));
    }
}