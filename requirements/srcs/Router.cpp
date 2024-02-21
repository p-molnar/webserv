/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Router.cpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tklouwer <tklouwer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/19 10:40:30 by tklouwer      #+#    #+#                 */
/*   Updated: 2024/02/16 10:15:10 by tklouwer      ########   odam.nl         */
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
    registerRoute("POST", &handlePostRequest);
    registerRoute("DELETE", &handleDeleteRequest);
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

    for (const auto& route : routes) 
    {
        if (method == route.request_method)
        {
            route.callback(&req, &res);
            return ;
        }
    }
}