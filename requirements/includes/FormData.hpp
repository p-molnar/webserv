#ifndef FORMDATA__HPP
#define FORMDATA__HPP

#include <string>
#include <map>
#include <vector>
#include <iostream>

#include "tokenizer.hpp"
#include "consts.hpp"

typedef struct s_form_overhead
{
	std::string raw_overhead;
	std::map<std::string, std::string> raw_headers;
	std::map<std::string, std::string> content_disposition;
	std::string content_type;

} t_form_overhead;

typedef struct s_form_data
{
	t_form_overhead overhead;
	std::string payload;
} t_form_data;

class FormData
{

private:
	std::string raw_data;
	std::vector<t_form_data> form_data;

public:
	FormData(const std::string &data, const std::map<std::string, std::string> &headers);
	~FormData();

private:
	t_form_overhead FormData::parseFormOverhead(std::string raw_overhead);
	std::string FormData::parseFormPayload(std::string raw_payload);
};

#endif