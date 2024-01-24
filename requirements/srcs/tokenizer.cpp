#include "tokenizer.hpp"

std::string strip(const std::string &input, std::string strip_chars)
{
	std::size_t start = input.find_first_not_of(strip_chars);
	std::size_t end = input.find_last_not_of(strip_chars);

	if (start == std::string::npos || end == std::string::npos)
	{
		return "";
	}

	return input.substr(start, end - start + 1);
}

std::vector<std::string> tokenize(const std::string &input,
								  const std::string &delimiter,
								  std::size_t max_count)
{
	std::vector<std::string> tokens;
	std::string token;

	size_t pos = 0;
	size_t found;

	while ((found = input.find(delimiter, pos)) != std::string::npos && tokens.size() < max_count)
	{
		token = input.substr(pos, found - pos);
		tokens.push_back(token);
		pos = found + delimiter.size();
	}

	token = input.substr(pos);
	if (!token.empty())
	{
		tokens.push_back(token);
	}

	return tokens;
}