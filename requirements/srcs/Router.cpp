/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Router.cpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tklouwer <tklouwer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/19 10:40:30 by tklouwer      #+#    #+#                 */
/*   Updated: 2024/01/29 14:07:14 by tklouwer      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Router.hpp"
#include <regex>
#include "FileHandler.hpp"
#include "Log.hpp"
#include "httpStatus.hpp"

Router::Router() 
{
    registerRoute("GET", &handleGetRequest);
    // registerRoute("POST", &handlePostRequest);
}
void    Router::registerRoute(std::string request_method,
            void (*callback)(const HttpRequest*, HttpResponse*))
{
    routes.push_back({request_method, callback});
}

void    Router::routeRequest(const HttpRequest& req, HttpResponse& res)
{
    Log::logMsg("Routing the request");
    std::string method = req.getRequestLineComp("method");

    if ((req.getRequestLineComp("method") == "GET" || req.getRequestLineComp("method") == "POST") && req.getType() == EXECUTABLE)
    {
        std::cout << "CGI OUTPUT" << RequestProcessor::executeCgi(req.getUriComps()) << std::endl;
        res.setBody(RequestProcessor::executeCgi(req.getUriComps()));
        httpStatus status(statusCode::OK);
        res.setStatusLine(status.getStatusLine());
    }
    else if (req.getRequestLineComp("method") == "GET" && req.getType() == RESOURCE)
    {
        // std::string s = fileHandler::readFileContent(req.getUriComps().path);
        std::string filePath = req.getUriComps().path;
        std::string filePath2 = filePath != "/" ? filePath : "srv/www/" + filePath;
        std::cout << filePath2 << "\n";
        std::string s = RequestProcessor::listDirectoryContent(filePath2);
        res.setBody(s);
        httpStatus status(statusCode::OK);
        res.setStatusLine(status.getStatusLine());
    }
    // for (const auto& route : routes) 
    // {
    //     if (method == route.request_method)
    //     {
    //         route.callback(&req, &res);
    //         return ;
    //     }
    // }
}