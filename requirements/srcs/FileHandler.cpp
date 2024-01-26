/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   FileHandler.cpp                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: tklouwer <tklouwer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/25 08:25:07 by tklouwer      #+#    #+#                 */
/*   Updated: 2024/01/26 11:49:26 by tklouwer      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "FileHandler.hpp"
#include "httpStatus.hpp"
#include <filesystem>
#include <iterator>
#include <fstream>
#include <iostream>
#include "Log.hpp"

bool fileHandler::fileExists(std::string& filePath)
{
    return std::filesystem::exists(filePath);
}

std::string fileHandler::readFileContent(const std::string& filePath)
{
    std::filesystem::path path{filePath};
    
    std::ifstream fileStream(filePath);
    if (!fileStream.is_open())
        throw std::runtime_error("Failed to open file " + filePath);
    
    return std::string(std::istreambuf_iterator<char>(fileStream), std::istreambuf_iterator<char>());
}

void     handleGetRequest(const httpRequest *req, httpResponse *res) 
{
    Log::logMsg("Handling GET request");
    // std::string uri = req->getHeader("request_uri"); // NOT WORKINGGGGG
    // if (uri.empty() || uri == "/")
    std::string uri = "/index.html";

    std::string filePath = "www" + uri;
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
        res->setHeaders("Content-Type", "text/html");
        res->setHeaders("Connection", "close");
    }
}