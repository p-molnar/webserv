/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   FileHandler.cpp                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: tklouwer <tklouwer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/25 08:25:07 by tklouwer      #+#    #+#                 */
/*   Updated: 2024/02/05 10:04:57 by tklouwer      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "FileHandler.hpp"
#include "httpStatus.hpp"
#include <filesystem>
#include <iterator>
#include <fstream>
#include <iostream>
#include "Log.hpp"
#include "RequestProcessor.hpp"
#include <sys/stat.h>

#define ERROR "<html><body><h1>404 Not Found</h1></body></html>"

bool fileHandler::isValidPath(std::string& file_path)
{
    struct stat buffer;
    return (stat(file_path.c_str(), &buffer) == 0);
}

bool fileHandler::isDirectory(std::string& file_path)
{
    struct stat buffer;
    return (stat(file_path.c_str(), &buffer) == 0 && S_ISDIR(buffer.st_mode));
}

bool fileHandler::isFile(std::string& file_path) 
{
    struct stat buffer;
    return (stat(file_path.c_str(), &buffer) == 0 && S_ISREG(buffer.st_mode));
}

std::string fileHandler::readFileContent(const std::string& file_path)
{
    std::ifstream file(file_path);
    if (!file.is_open())
    {
        Log::logMsg("Error opening file");
        throw std::runtime_error("Failed to open file " + file_path);
    }
    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();
    return content;
}

void     handleGetRequest(const HttpRequest *req, HttpResponse *res) 
{
    Log::logMsg("Handling GET request");

    const std::string root_dir = Config::getConfig()->getRoot();
    std::string file_path = req->getUriComps().www_path;
    if (file_path.find(".py") != std::string::npos)
    {
        res->setStatusLineAndBody(httpStatus::getStatusLine(statusCode::OK),
            RequestProcessor::executeCgi(req->getUriComps()));
    }
    if (file_path.find(".") == std::string::npos && req->getType() == RESOURCE && !fileHandler::isDirectory(file_path)) {
        file_path += ".html";
    }
    if (!fileHandler::isValidPath(file_path) && req->getType() != EXECUTABLE) {
        res->setStatusLineAndBody(httpStatus::getStatusLine(statusCode::NotFound), 
            fileHandler::readFileContent(root_dir + "/error.html"));
        return ;
    }
    if (fileHandler::isValidPath(file_path))
    {
        std::string s;
        if (fileHandler::isDirectory(file_path))
            s = RequestProcessor::listDirectoryContent(file_path);
        else if (fileHandler::isFile(file_path))
            s = fileHandler::readFileContent(file_path);
        res->setStatusLineAndBody(httpStatus::getStatusLine(statusCode::OK), s);
    }
}

void     handlePostRequest(const HttpRequest *req, HttpResponse *res)
{
    Log::logMsg("Handling POST request");
    std::string file_path = req->getUriComps().path;
    std::cout << file_path << std::endl;
    RequestProcessor::uploadFiles(req->getFormDataObj());
    res->setStatusLine(httpStatus::getStatusLine(statusCode::OK));
}