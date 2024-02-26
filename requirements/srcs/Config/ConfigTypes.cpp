/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ConfigTypes.cpp                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: tklouwer <tklouwer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/26 12:13:12 by tklouwer      #+#    #+#                 */
/*   Updated: 2024/02/26 12:13:37 by tklouwer      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ConfigTypes.hpp"

int ConfigType::getInt()
{
	throw std::invalid_argument("getInt() is the wrong conversion type of ConfigType");
}

std::string ConfigType::getString()
{
	throw std::invalid_argument("getString() is the wrong conversion type of ConfigType");
}

ConfigInt::ConfigInt(int val)
{
	_int_val = val;
}

int	ConfigInt::getInt()
{
	return _int_val;
}

ConfigInt::~ConfigInt() {}

ConfigStr::ConfigStr(std::string val)
{
	_str_val = val;
}

std::string ConfigStr::getString()
{
	return (_str_val);
}

ConfigStr::~ConfigStr() {}
