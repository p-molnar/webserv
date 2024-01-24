#include "FormData.hpp"

t_form_overhead FormData::parseFormOverhead(std::string raw_overhead)
{
	t_form_overhead overhead_data;
	overhead_data.raw_overhead = raw_overhead;

	std::vector<std::string> raw_headers = tokenize(raw_overhead, CRLF);
	std::vector<std::string>::iterator it = raw_headers.begin();
	std::vector<std::string>::iterator ite = raw_headers.end();

	while (it != ite)
	{
		std::vector<std::string> header_comps = tokenize(*it, HEADER_SEP);
		if (header_comps.size() != 2)
			throw std::runtime_error("overhead header parse error");

		overhead_data.raw_headers[header_comps[0]] = header_comps[1];
		it++;
	}
	std::vector<std::string> content_disposition_comps = tokenize(overhead_data.raw_headers.at("Content-Disposition"), SEMICOL);
	it = content_disposition_comps.begin();
	ite = content_disposition_comps.end();

	while (it != ite)
	{
		std::vector<std::string> content_disposition_val_comps = tokenize(*it, "=");
		if (content_disposition_val_comps.size() == 1)
			overhead_data.content_disposition["data_type"] = *it;
		else if (content_disposition_val_comps.size() == 2)
			overhead_data.content_disposition[content_disposition_val_comps[0]] = strip(*it, "\"");
		else
			throw std::runtime_error("Content-Disposition parse error");
		it++;
	}
}

std::string FormData::parseFormPayload(std::string raw_payload)
{
}

FormData::FormData(const std::string &data, const std::map<std::string, std::string> &headers)
{
	raw_data = data;
	std::string content_type_field_val = headers.at("Content-Type");
	const std::string boundary_key = "boundary=";
	std::size_t boundary_pos = content_type_field_val.find(boundary_key);

	if (boundary_pos != NPOS)
	{
		std::string boundary = content_type_field_val.substr(boundary_pos + boundary_key.length());
		std::vector<std::string> raw_data = tokenize(data, boundary);

		std::vector<std::string>::iterator it = raw_data.begin();
		std::vector<std::string>::iterator ite = raw_data.end();

		while (it != ite)
		{
			if (*it != "--")
			{
				std::vector<std::string> form_comps = tokenize(*it, DBL_CRLF);
				if (form_comps.size() != 2)
					throw std::runtime_error("form parse error");

				t_form_overhead overhead = parseFormOverhead(form_comps[0]);
				std::string payload = parseFormPayload(form_comps[1]);

				form_data.push_back((t_form_data){overhead, payload});

				std::cout << "form raw data: " << *it << "\n";
			}
			it++;
		}
	}
}
FormData::~FormData() {}