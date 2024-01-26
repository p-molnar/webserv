/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   FileHandler.cpp                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: tklouwer <tklouwer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/25 08:25:07 by tklouwer      #+#    #+#                 */
/*   Updated: 2024/01/26 09:51:20 by tklouwer      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "FileHandler.hpp"
#include "httpStatus.hpp"
#include <fstream>
#include <sstream>
#include "Log.hpp"

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
    Log::logMsg("Handling GET request");
    // std::string uri = req->getHeader("request_uri");
    // if (uri.empty() || uri == "/")
    std::string uri = "/index.html";
    
    std::string filePath = "www" + uri;
    std::cout << "\n\n" << filePath << "\n\n" << std::endl;
    if (fileHandler::fileExists(filePath))
    {
        Log::logMsg("File exists");
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
        res->generateResponse(true);
    }
}