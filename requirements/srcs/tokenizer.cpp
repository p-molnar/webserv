#include "tokenizer.hpp"

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