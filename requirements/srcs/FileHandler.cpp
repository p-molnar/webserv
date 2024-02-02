/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   FileHandler.cpp                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: tklouwer <tklouwer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/25 08:25:07 by tklouwer      #+#    #+#                 */
/*   Updated: 2024/02/02 13:35:22 by tklouwer      ########   odam.nl         */
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

#define ERROR "<html><body><h1>404 Not Found</h1></body></html>"

bool fileHandler::fileExists(std::string& file_path)
{
    return std::filesystem::exists(file_path);
}

std::string fileHandler::readFileContent(const std::string& file_path)
{
    std::filesystem::path path{file_path};
    
    std::ifstream fileStream(file_path);
    if (!fileStream.is_open())
        throw std::runtime_error("Failed to open file " + file_path);
    
    return std::string(std::istreambuf_iterator<char>(fileStream), std::istreambuf_iterator<char>());
}

bool fileHandler::isDirectory(std::string& file_path)
{
    return std::filesystem::is_directory(std::filesystem::path(file_path));
}

bool fileHandler::isFile(std::string& file_path) {
       return std::filesystem::is_regular_file(std::filesystem::path(file_path));
}

void     handleGetRequest(const HttpRequest *req, HttpResponse *res) 
{
    Log::logMsg("Handling GET request");

    const std::string root_dir = "srv/www";
    std::string file_path = req->getUriComps().path;

    if (file_path.find(".py") != std::string::npos)
    {
        res->setStatusLineAndBody(httpStatus::getStatusLine(statusCode::OK),
            RequestProcessor::executeCgi(req->getUriComps()));
    }
    file_path = file_path.empty() || file_path == "/" ? root_dir : root_dir + file_path;
    if (file_path.find(".") == std::string::npos && req->getType() == RESOURCE && !fileHandler::isDirectory(file_path)) {
        file_path += ".html";
    }
    if (!fileHandler::fileExists(file_path) && req->getType() != EXECUTABLE) {
        res->setStatusLineAndBody(httpStatus::getStatusLine(statusCode::NotFound), 
            fileHandler::readFileContent(root_dir + "/error.html"));
        return ;
    }
    if (fileHandler::fileExists(file_path))
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