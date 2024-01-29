/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   FileHandler.cpp                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: tklouwer <tklouwer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/25 08:25:07 by tklouwer      #+#    #+#                 */
/*   Updated: 2024/01/29 13:55:41 by tklouwer      ########   odam.nl         */
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
    std::string filePath2 = filePath != "/" ? "srv/www/" + filePath : "srv/www/index.html";
    
    
    std::filesystem::path path{filePath2};
    
    std::ifstream fileStream(filePath2);
    if (!fileStream.is_open())
        throw std::runtime_error("Failed to open file " + filePath2);
    
    return std::string(std::istreambuf_iterator<char>(fileStream), std::istreambuf_iterator<char>());
}

void     handleGetRequest(const HttpRequest */*  */, HttpResponse *res) 
{
    Log::logMsg("Handling GET request");
    // std::string uri = req->getHeader("request_uri"); // NOT WORKINGGGGG
    // if (uri.empty() || uri == "/")
    std::string uri = "/index.html";

    // if (req->getHeader("connection") == "close") check getHeader function not working correctly. 
    //     res->setHeaders("connection", "close");
    std::string filePath = "srv/www" + uri;
    if (fileHandler::fileExists(filePath))
    {
        Log::logMsg("File exists");
        std::string content = fileHandler::readFileContent(filePath);
        httpStatus status(statusCode::OK);
        res->setStatusLine(status.getStatusLine());
        res->setBody(content);
    }
}