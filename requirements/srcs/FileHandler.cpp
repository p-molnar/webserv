/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   FileHandler.cpp                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: tklouwer <tklouwer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/25 08:25:07 by tklouwer      #+#    #+#                 */
/*   Updated: 2024/02/16 13:41:34 by tklouwer      ########   odam.nl         */
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
#include <cstdio>


#define ERROR "<html><body><h1>404 Not Found</h1></body></html>"

bool fileHandler::isValidPath(std::string& file_path)
{
    return std::filesystem::exists(file_path);
}

bool fileHandler::deleteResource(const std::string& file_path) 
{
    Log::logMsg("Handling DELETE request");

    try {
        std::filesystem::remove_all(file_path);
    } 
    catch (const std::filesystem::filesystem_error& e) {
        std::string error_message = "Filesystem error: " + std::string(e.what());
        Log::logMsg(error_message);
        throw std::runtime_error(error_message);
    }

    Log::logMsg("File(s) deleted from server: " + file_path);
    return true;
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
        res->setStatusLineAndBody(httpStatus::getStatusLine(statusCode::not_found), 
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
    RequestProcessor::uploadFiles(req->getFormDataObj());
    res->setStatusLine(httpStatus::getStatusLine(statusCode::OK));
}

void handleDeleteRequest(const HttpRequest *req, HttpResponse *res) 
{
    std::string file_path = req->getUriComps().path;
    if (!file_path.empty() && file_path[0] == '/') // absolute path does not concatenate with '/' as fist occurence in str
        file_path.erase(0, 1);

    std::filesystem::path cwd = std::filesystem::current_path();
    std::filesystem::path root_path(Config::getConfig()->getRoot());
    std::filesystem::path relative_path(file_path);
    std::filesystem::path absolute_path = cwd / root_path / relative_path;
    try {
        if (std::filesystem::exists(absolute_path)) {
            fileHandler::deleteResource(absolute_path.string());
            res->setStatusLineAndBody(httpStatus::getStatusLine(statusCode::OK), "");
        } else {
            throw std::runtime_error("File not found: " + file_path);
        }
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << '\n';
        res->setStatusLineAndBody(httpStatus::getStatusLine(statusCode::not_found), "<html><body><h1>" + httpStatus::_message.at(statusCode::not_found) + "</h1></body></html>");
    }
}
