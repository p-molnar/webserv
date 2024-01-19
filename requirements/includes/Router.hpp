/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Router.hpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tklouwer <tklouwer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/19 10:36:07 by tklouwer      #+#    #+#                 */
/*   Updated: 2024/01/19 13:47:45 by tklouwer      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <vector>
#include "httpRequest.hpp"
#include "httpResponse.hpp"
#include <iostream>

class Router {

    struct Route {
        std::string url_regex;
        std::string request_method;
        void (*callback)(const httpRequest*, httpResponse*);
    };

    std::vector<Route> routes;

    public:
        void    registerRoute(std::string url_regex, std::string request_method, void (*callback)(const httpRequest*, httpResponse*));
        void    routeRequest(const httpRequest& req, httpResponse&);
};
