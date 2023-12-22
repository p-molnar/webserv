#include "httpRequest.hpp"
#include "WebServer.hpp"
#include <string>

httpRequest::httpRequest(const std::string& requestText)
{
    parseRequest(requestText);
}

void    httpRequest::parseRequest(const std::string& requestText)
{
    this->_method = parseRequestLine(requestText);
    std::cout << this->_method << std::endl;
}

std::string     httpRequest::parseRequestLine(std::string& line)
{
    size_t firstSpace = line.find(' ');
    if (firstSpace != std::string::npos)
        return line.substr(0, firstSpace);
    return "";
}