/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   errors.hpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tklouwer <tklouwer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/26 12:10:40 by tklouwer      #+#    #+#                 */
/*   Updated: 2024/02/26 12:10:44 by tklouwer      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_HPP
#define ERRORS_HPP

/* C/C++ Libs */
#include <string.h>
#include <cerrno>

#define STRERR std::string(strerror(errno))

#endif