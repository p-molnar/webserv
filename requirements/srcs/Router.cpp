/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Router.cpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tklouwer <tklouwer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/19 10:40:30 by tklouwer      #+#    #+#                 */
/*   Updated: 2024/01/25 14:21:48 by tklouwer      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Router.hpp"
#include <regex>
#include "FileHandler.hpp"

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
    std::cout << "ROUTE\n";
    std::string method = req.getRequestLine("method");

    for (const auto& route : routes) 
    {
        if (method == route.request_method)
        {
            route.callback(&req, &res);
            return ;
        }
    }
}