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
    std::string uri = "/index1.html";
    std::string filePathNotFound = "www/error.html";
    
    std::string filePath = "www" + uri;
    if (fileHandler::fileExists(filePath))
    {
        Log::logMsg("File exists");
        std::cout << "\n\n" << filePath << "\n\n" << std::endl;
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
    else if (fileHandler::fileExists(filePathNotFound))
    {
        Log::logMsg("File not found");
        std::cout << "\n\n" << filePathNotFound << "\n\n" << std::endl;
        std::string content = fileHandler::readFileContent(filePathNotFound);
        httpStatus status(statusCode::NotFound);
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
    else
    {
        Log::logMsg("Error file not found");
        std::cout << "\n\n" << filePath << "\n\n" << std::endl;
    }
}