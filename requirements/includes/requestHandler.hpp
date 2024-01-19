/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   requestHandler.hpp                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: tklouwer <tklouwer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/19 13:41:13 by tklouwer      #+#    #+#                 */
/*   Updated: 2024/01/19 13:45:37 by tklouwer      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "httpRequest.hpp"
#include "httpResponse.hpp"


void    handleGetRequest(const httpRequest *req, httpResponse *res);
