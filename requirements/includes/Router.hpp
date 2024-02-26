/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Router.hpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tklouwer <tklouwer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/19 10:36:07 by tklouwer      #+#    #+#                 */
/*   Updated: 2024/02/26 12:01:51 by tklouwer      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#pragma once

/* C/C++ Libs */
#include <string>
#include <vector>
#include <regex>

/* Webserv */
#include "RequestHandler.hpp"

class Router {

    struct Route {
        std::string request_method;
        void (*callback)(const HttpRequest*, HttpResponse*);
    };

    std::vector<Route> routes;

    public:
        Router();
        ~Router() {};
        void    registerRoute(std::string request_method, void (*callback)(const HttpRequest*, HttpResponse*));
        void    routeRequest(const HttpRequest& req, HttpResponse&);
};
