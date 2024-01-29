/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Router.hpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tklouwer <tklouwer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/19 10:36:07 by tklouwer      #+#    #+#                 */
/*   Updated: 2024/01/29 11:14:26 by tklouwer      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <vector>
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include <iostream>

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
