/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   RequestHandler.cpp                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: tklouwer <tklouwer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/25 08:25:07 by tklouwer      #+#    #+#                 */
/*   Updated: 2024/02/27 14:10:20 by tklouwer      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "RequestHandler.hpp"

void handleGetRequest(const HttpRequest *req, HttpResponse *res)
{
    Log::logMsg("Handling GET request");
    std::string file_path = req->getUriComps().path;
    const std::string root_dir = req->getServerConfig()->getRoot();

    Log::logMsg(file_path);
    if (req->getType() == EXECUTABLE)
    {
        fileHandler::handleExecutableRequest(req, res);
        return;
    }
    if (file_path.find(".") == std::string::npos && req->getType() == RESOURCE && !fileHandler::isDirectory(file_path))
        file_path += ".html";

    if (!fileHandler::isValidPath(file_path) && req->getType() != EXECUTABLE)
    {
        fileHandler::handleErrorResponse(404, req, res);
        return;
    }
    if (fileHandler::isValidPath(file_path))
    {
        if (fileHandler::isDirectory(file_path))
            fileHandler::serveDirectoryListing(req, res);
        else if (fileHandler::isFile(file_path))
            fileHandler::serveStaticFile(file_path, res);
    }
}

void handlePostRequest(const HttpRequest *req, HttpResponse *res)
{
    Log::logMsg("Handling POST request");
    std::string file_path = req->getUriComps().path;
    RequestProcessor::uploadFiles(req->getFormDataObj());
    res->setStatusLine(httpStatus::getStatusLine(statusCode::OK));
}

void handleDeleteRequest(const HttpRequest *req, HttpResponse *res)
{
    std::filesystem::path absolute_path = fileHandler::getAbsolutePath(req->getUriComps().path, req->getServerConfig()->getRoot());
    try
    {
        if (std::filesystem::exists(absolute_path))
        {
            fileHandler::deleteResource(absolute_path.string());
            res->setStatusLineAndBody(httpStatus::getStatusLine(statusCode::OK), "");
        }
        else
        {
            throw std::runtime_error("File not found: " + absolute_path.string());
        }
    }
    catch (const std::runtime_error &e)
    {
        std::cerr << e.what() << '\n';
        res->setStatusLineAndBody(httpStatus::getStatusLine(statusCode::not_found),
                                  "<html><body><h1>" + httpStatus::_message.at(statusCode::not_found) + "</h1></body></html>");
    }
}
