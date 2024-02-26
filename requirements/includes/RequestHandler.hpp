/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   RequestHandler.hpp                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: tklouwer <tklouwer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/26 11:54:07 by tklouwer      #+#    #+#                 */
/*   Updated: 2024/02/26 12:04:28 by tklouwer      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HANDLER_HPP
#define REQUEST_HANDLER_HPP

/* Webserv */
#include "FileHandler.hpp"

void handleGetRequest(const HttpRequest *req, HttpResponse *res);
void handlePostRequest(const HttpRequest *req, HttpResponse *res);
void handleDeleteRequest(const HttpRequest *req, HttpResponse *res);

#endif