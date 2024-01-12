#pragma once
#ifndef CONFIG_TYPES
#define CONFIG_TYPES

#include <vector>
#include <string>

class ConfigType
{

};

class ConfigInt : public ConfigType
{
	int int_val;
};

class ConfigVecInt : public ConfigType
{
	std::vector<int> vec_int_val;
};

class ConfigStr : public ConfigType
{
	std::string str_val;
};

class ConfigVecStr : public ConfigType
{
	std::vector<std::string> vec_str_val;
};

#endif
