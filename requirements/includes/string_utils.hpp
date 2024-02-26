/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   string_utils.hpp                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: tklouwer <tklouwer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/26 12:12:08 by tklouwer      #+#    #+#                 */
/*   Updated: 2024/02/26 12:12:12 by tklouwer      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRING_UTILS__HPP
#define STRING_UTILS__HPP

/* C/C++ Libs */
#include <vector>
#include <string>

std::string strip(const std::string &input, std::string strip_chars);
std::vector<std::string> tokenize(const std::string &input,
								  const std::string &delimiter,
								  std::size_t max_count = -1);
std::string readFull(int fd);
#endif