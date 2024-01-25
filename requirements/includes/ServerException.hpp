/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ServerException.hpp                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: tklouwer <tklouwer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/25 08:52:51 by tklouwer      #+#    #+#                 */
/*   Updated: 2024/01/25 09:38:09 by tklouwer      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVEREXCEPTION_HPP
#define SERVEREXCEPTION_HPP

#include <stdexcept>
#include "httpResponse.hpp"
#include "httpStatus.hpp"

class ServerException : public httpStatus, public std::runtime_error {
    public: 
        ServerException(statusCode status) : 
            httpStatus(status), std::runtime_error(getStatusLine()) {};
};

#endif