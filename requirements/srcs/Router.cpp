/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Router.cpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tklouwer <tklouwer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/19 10:40:30 by tklouwer      #+#    #+#                 */
/*   Updated: 2024/01/29 11:00:24 by tklouwer      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Router.hpp"
#include <regex>
#include "FileHandler.hpp"
#include "Log.hpp"

Router::Router() 
{
    registerRoute("GET", &handleGetRequest);
    // registerRoute("POST", &handlePostRequest);
}
void    Router::registerRoute(std::string request_method,
            void (*callback)(const httpRequest*, httpResponse*))
{
    routes.push_back({request_method, callback});
}

void    Router::routeRequest(const httpRequest& req, httpResponse& res)
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