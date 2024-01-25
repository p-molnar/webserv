/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   requestHandler.cpp                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: tklouwer <tklouwer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/19 13:41:51 by tklouwer      #+#    #+#                 */
/*   Updated: 2024/01/25 13:34:48 by tklouwer      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "requestHandler.hpp"
#include "FileHandler.hpp"

// void     handleGetRequest(const httpRequest *req, httpResponse *res) 
// {
//     std::string uri = req->getHeader("request_uri");
//     if (uri.empty() || uri == '/')
//         uri = "/index.html";
    
//     std::string filePath = "../www" + uri;
//     const auto& headers = req->getHeaders();
//     for (const auto& header : headers)
//     {
//         res->setHeaders(header.first, header.second);
//     }
// }