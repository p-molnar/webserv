#include "httpRequest.hpp"
#include "WebServer.hpp"
#include <string>

httpRequest::httpRequest(const std::string& requestText)
{
    try {
        parseRequest(requestText);
    } catch (const std::runtime_error& e) {
        std::cerr << "Error parsing HTTP request: " << e.what() << std::endl;
        throw;
    }
}

void    httpRequest::parseRequest(const std::string& requestText)
{
    size_t firstline = requestText.find("\r\n");
    if (firstline == std::string::npos) {
        throw std::runtime_error("Invalid request line");
    }
    if (firstline != std::string::npos)
    {
        parseRequestLine(requestText.substr(0, firstline));
        std::string headersText = requestText.substr(firstline + 2);
        parseHeaders(headersText);
    }
}

void    httpRequest::parseRequestLine(const std::string& line)
{
    size_t firstSpace = line.find(' ');
        if (firstSpace == std::string::npos) {
        throw std::runtime_error("Invalid request line");
    }
    if (firstSpace != std::string::npos)
        this->_method = line.substr(0, firstSpace);
}

void    httpRequest::parseHeaders(const std::string& headers)
{
    std::string::size_type start = 0;
    std::string::size_type end;

    while ((end = headers.find("\r\n", start)) != std::string::npos)
    {
        std::string line = headers.substr(start, end - start);
        std::string::size_type delimiter = line.find(':');
        if (delimiter == std::string::npos) {
            throw std::runtime_error("Malformed header line: " + line);
        }
        if (delimiter != std::string::npos)
        {
            std::string key = line.substr(0, delimiter);
            std::string value = line.substr(delimiter + 2);
            _headers[key] = value;
            // THROWS IMMEDIATE EXCEPTION HANDLE DUPLICATE HEADERS> ESPECIALLY IN CHUNCKS
            // if (_headers.find(key) != _headers.end()) {
            //     throw std::runtime_error("Duplicate headers");
            // }
        }
        start = end + 2;
    }
}

std::string httpRequest::getMethod() const
{
    return _method;
}

std::string httpRequest::getHeader(const std::string& headerName) const
{
    auto it = _headers.find(headerName);
    if (it != _headers.end())
        return it->second;
    return "";
}