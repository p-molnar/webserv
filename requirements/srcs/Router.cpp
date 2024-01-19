/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Router.cpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tklouwer <tklouwer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/19 10:40:30 by tklouwer      #+#    #+#                 */
/*   Updated: 2024/01/19 12:43:02 by tklouwer      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Router.hpp"
#include <regex>

void    Router::registerRoute(std::string url_regex, std::string request_method,
            void (*callback)(const httpRequest*))
{
    Route route;
    route.url_regex = url_regex;
    route.request_method = request_method;
    route.callback = callback;
    routes.push_back(route);
}

void    Router::routeRequest(const httpRequest& req)
{
    for (auto& r : routes) {
        std::regex pat {r.url_regex};
        std::smatch match;

    std::string tmp = req.getRequestLine("request_uri");
    if ((std::regex_match(tmp, match, pat))
        && (req.getRequestLine("method").compare(r.request_method) == 0))
        {
            r.callback(&req);
            break ;
        }
    }
}